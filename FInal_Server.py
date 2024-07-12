import paho.mqtt.client as mqtt
import json
import base64
from cryptography.hazmat.primitives import serialization
from cryptography.hazmat.primitives.asymmetric import padding
from cryptography.hazmat.primitives import hashes

MQTT_BROKER_IP = "192.168.1.17"

# Paths to key files
private_key_path = 'D:\\GP\\Server\\private_key.pem'

# Loading private key
with open(private_key_path, 'rb') as f:
    private_key = serialization.load_pem_private_key(f.read(), password=None)

# MQTT settings
received_chunks = {}
total_chunks = {}
public_keys = {}

def on_connect(client, userdata, flags, rc):
    print("Connected with result code " + str(rc))
    client.subscribe("cars/+/data")
    client.subscribe("cars/public_keys")

def on_message(client, userdata, msg):
    try:
        if msg.topic == "cars/public_keys":
            process_public_key_chunk(msg)
        else:
            process_data_chunk(client, msg)
    except Exception as e:
        print(f"Error processing message: {e}")

def process_public_key_chunk(msg):
    try:
        payload = msg.payload.decode()
        chunk_meta, chunk_data = payload.split(':', 1)
        chunk_meta_parts = chunk_meta.split('/')
        
        if len(chunk_meta_parts) != 3:
            raise ValueError("Invalid chunk metadata format")

        car_id = chunk_meta_parts[0]
        chunk_index = int(chunk_meta_parts[1])
        chunk_total = int(chunk_meta_parts[2])

        if chunk_index > chunk_total or chunk_index < 1:
            raise IndexError("Chunk index out of range")

        if car_id not in received_chunks:
            received_chunks[car_id] = [None] * chunk_total
            total_chunks[car_id] = 0

        received_chunks[car_id][chunk_index - 1] = chunk_data
        total_chunks[car_id] += 1

        if total_chunks[car_id] == chunk_total:
            full_key_pem = ''.join(received_chunks[car_id])

            public_key = serialization.load_pem_public_key(full_key_pem.encode())
            public_keys[car_id] = public_key

            print(f"Stored public key for car {car_id}")

            del received_chunks[car_id]
            del total_chunks[car_id]

    except (ValueError, IndexError) as e:
        print(f"Error processing public key chunk: {e}")

def process_data_chunk(client, msg):
    try:
        payload = msg.payload.decode()
        chunk_meta, chunk_data = payload.split(':', 1)
        chunk_meta_parts = chunk_meta.split('/')
        
        if len(chunk_meta_parts) != 4:
            raise ValueError("Invalid chunk metadata format")

        car_id = chunk_meta_parts[0]
        chunk_index = int(chunk_meta_parts[2])
        chunk_total = int(chunk_meta_parts[3])

        if chunk_index > chunk_total or chunk_index < 1:
            raise IndexError("Chunk index out of range")

        if car_id not in received_chunks:
            received_chunks[car_id] = [None] * chunk_total
            total_chunks[car_id] = 0

        received_chunks[car_id][chunk_index - 1] = chunk_data
        total_chunks[car_id] += 1

        if total_chunks[car_id] == chunk_total:
            full_data_base64 = ''.join(received_chunks[car_id])


            encrypted_data = base64.b64decode(full_data_base64)


            # Decrypt the message
            decrypted_message = private_key.decrypt(
                encrypted_data,
                padding.OAEP(
                    mgf=padding.MGF1(algorithm=hashes.SHA256()),
                    algorithm=hashes.SHA256(),
                    label=None
                )
            )

            data = json.loads(decrypted_message.decode('utf-8'))
            print(f"Decrypted data from car {car_id}: {data}")
            process_data(client, car_id, data)

            del received_chunks[car_id]
            del total_chunks[car_id]

    except (ValueError, IndexError) as e:
        print(f"Error processing data chunk: {e}")

def process_data(client, car_id, data):
    # Determine the target car ID based on the sending car ID
    target_car_id = "Car2" if car_id == "Car1" else "Car1"

    # Printing the target location
    print(f"Target location ID: {target_car_id}")  # Print the target car ID
    
    if data.get("hardBraking"):
        message = json.dumps({"car_id": car_id, "event": "hardBraking"})
        encrypted_message = encrypt_message(target_car_id, message)
        publish_chunked_message(client, f"cars/{target_car_id}/commands", car_id, encrypted_message)
        print(f"Car {car_id} reported hard braking.")

    if data.get("Dim_Light"):
        message = json.dumps({"car_id": car_id, "event": "Dim_Light"})
        encrypted_message = encrypt_message(target_car_id, message)
        publish_chunked_message(client, f"cars/{target_car_id}/commands", car_id, encrypted_message)
        print(f"Car {car_id} reported dim light detection.")

    if data.get("overtaking_request"):
        message = json.dumps({"car_id": car_id, "event": "overtaking_request"})
        encrypted_message = encrypt_message(target_car_id, message)
        publish_chunked_message(client, f"cars/{target_car_id}/commands", car_id, encrypted_message)
        print(f"Car {car_id} requested to overtake.")

    if data.get("overtaking_response"):
        if data.get("overtaking_action"):
            message = json.dumps({"car_id": car_id, "event": "overtaking_approved"})
            encrypted_message = encrypt_message(target_car_id, message)
            publish_chunked_message(client, f"cars/{target_car_id}/commands", car_id, encrypted_message)
            print(f"Car {car_id} approved the overtaking.")
        else:
            message = json.dumps({"car_id": car_id, "event": "overtaking_denied"})
            encrypted_message = encrypt_message(target_car_id, message)
            publish_chunked_message(client, f"cars/{target_car_id}/commands", car_id, encrypted_message)
            print(f"Car {car_id} denied the overtaking.")

def encrypt_message(target_car_id, message):
    # Retrieve the public key for the target car ID
    public_key = public_keys[target_car_id]
    encrypted_message = public_key.encrypt(
        message.encode('utf-8'),
        padding.OAEP(
            mgf=padding.MGF1(algorithm=hashes.SHA256()),
            algorithm=hashes.SHA256(),
            label=None
        )
    )
    encrypted_message_base64 = base64.b64encode(encrypted_message).decode('utf-8')
    return encrypted_message_base64

def publish_chunked_message(client, topic, car_id, encrypted_message):
    chunk_size = 128
    total_data_chunks = (len(encrypted_message) + chunk_size - 1) // chunk_size

    for i in range(total_data_chunks):
        chunk = encrypted_message[i*chunk_size:(i+1)*chunk_size]
        chunk_meta = f"{car_id}/data/{i+1}/{total_data_chunks}:{chunk}"
        client.publish(topic, chunk_meta)

client = mqtt.Client()
client.on_connect = on_connect
client.on_message = on_message

client.connect(MQTT_BROKER_IP, 1883, 60)
client.loop_forever()
