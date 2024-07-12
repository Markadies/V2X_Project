#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <HardwareSerial.h>
#include <esp_task_wdt.h>
#include <FS.h>
#include <SPIFFS.h>
#include <mbedtls/pk.h>
#include <mbedtls/entropy.h>
#include <mbedtls/ctr_drbg.h>
#include <mbedtls/base64.h>
#include <mbedtls/md.h>

#define MAX_ALLOWED_TIME_IN_MILLIS  5
#define CHUNK_SIZE 128  // Define the chunk size

HardwareSerial SerialPort(2);
String Buffer;
String Global_fGPS_Latitude  = "30.09471";
String Global_fGPS_Longitude = "31.31403";
String Global_uint16Speed    = "1";
const char* ssid = "Bendary";
const char* password = "01276047636rr";
const char* car_id = "Car2";  // Define the car ID
bool overtaking_response = false;
bool overtaking_request = false;
bool overtaking_action = false;
bool hardBraking_alert = false;
bool dimLights_detect = false;
bool publish_Ready = false;
const char* mqttServer = "192.168.1.17";

// MQTT topics
const char* pub_topic = "cars/Car2/data";
const char* sub_topic = "cars/Car2/commands";
const char* pub_key_topic = "cars/public_keys";

WiFiClient Car2;
PubSubClient client(Car2);
const int MAX_CHUNKS = 3;
int totalChunks = 0;
String receivedChunks[MAX_CHUNKS];

int receivedDataChunksCount = 0;
int receivedCount = 0;

void setup();
void setup_wifi();
void loop();
void reconnect();
void onUARTReceive();
void Decode_GPSSpeedArray(String Copy_fGPS_Latitude, String Copy_fGPS_Longitude, String Copy_uint16Speed, uint8_t Copy_uint8FirstIndex, uint8_t Copy_uint8LastIndex);
String readKey(const char* path);
void encryptAndPublish(const char* message);
void publishData();
void publishPublicKey();
void callback(char* topic, byte* message, unsigned int length);
void decryptMessage(const String& encryptedBase64, const String& privateKey);

void setup() {
  Serial.begin(115200);
  if (!SPIFFS.begin(true)) {
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }
  setup_wifi();
  SerialPort.begin(115200, SERIAL_8N1, 16, 17); 
  SerialPort.onReceive(onUARTReceive);
  client.setCallback(callback);
  client.setServer(mqttServer, 1883);
  pinMode(2, OUTPUT); 

  /* Debugging section */
  reconnect();
  delay(4300);
  overtaking_response = true;
  overtaking_action = false;
  publishData();
  
}

void setup_wifi() {
  delay(10);
  Serial.println("Connecting to WiFi...");
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected.");
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  if(publish_Ready == true)
  {
    publishData();
  }
  client.loop();
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect("Car2")) {
      Serial.println("connected");
      if (client.subscribe(sub_topic)) {
        Serial.println("Subscribed to topic: cars/Car2/commands");
      } else {
        Serial.println("Failed to subscribe to topic");
      }
      publishPublicKey();
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(500);
    }
  }
}

void onUARTReceive() {
  uint8_t i, j;
  uint32_t Local_uint32TimeNow;
  bool Local_uint32TimeOutErrorCode = false;

  digitalWrite(2, HIGH);
 
  if (SerialPort.available()) {
    Buffer = SerialPort.readStringUntil('!');
    Serial.println("Received Data");
    Serial.print(Buffer);

    Local_uint32TimeNow = millis();
    for(i = 0; (Buffer[i] != '#') && (Buffer[i] != '%'); i++) {
      if((millis()-Local_uint32TimeNow) > MAX_ALLOWED_TIME_IN_MILLIS) {
        Local_uint32TimeOutErrorCode = true;
        Serial.println("Timeout occurred");
        break;
      }
    }
    if(Local_uint32TimeOutErrorCode == false) {
      if(Buffer[i] == '%') {
        if(Buffer[i+1]== 'B')
        {
         hardBraking_alert = true;
         publish_Ready = true;
        }
        else if(Buffer[i+1]== 'T')
        {
          overtaking_response = true;
          overtaking_action = true;
          publish_Ready = true;
        }
        else if(Buffer[i+1]== 'F')
        {
          overtaking_response = true;
          overtaking_action = false;
          publish_Ready = true;
        }
        else
        {
          /* Do Nothing */
        }
  
      } else if(Buffer[i] == '#') {
        for(j = i; Buffer[j] != '^'; j++) {
          // Loop to find the end index
        }
        Decode_GPSSpeedArray(Global_fGPS_Latitude, Global_fGPS_Longitude, Global_uint16Speed, i, j);
         publish_Ready = true;
      }
    }
  }
  digitalWrite(2, LOW);
}

void Decode_GPSSpeedArray(String Copy_fGPS_Latitude, String Copy_fGPS_Longitude, String Copy_uint16Speed, uint8_t Copy_uint8FirstIndex, uint8_t Copy_uint8LastIndex) {
    // Decoding logic 
    String longitudeStr = Buffer.substring(Copy_uint8FirstIndex + 1, Buffer.indexOf('*', Copy_uint8FirstIndex));
    String latitudeStr  = Buffer.substring(Buffer.indexOf('*', Copy_uint8FirstIndex) + 1, Buffer.indexOf('&',Copy_uint8FirstIndex));
    String speedStr     = Buffer.substring(Buffer.indexOf('&',Copy_uint8FirstIndex) + 1, Buffer.indexOf('^',Copy_uint8FirstIndex));

    Global_fGPS_Latitude = latitudeStr;
    Global_fGPS_Longitude = longitudeStr;
    Global_uint16Speed = speedStr;
}

String readKey(const char* path) {
  File file = SPIFFS.open(path, "r");
  if (!file) {
    Serial.print("Failed to open key file: ");
    Serial.println(path);
    return "";
  }

  String key = file.readString();
  file.close();
  return key;
}

void publishPublicKey() {
  String CarpublicKey = readKey("/car2_public_key.pem");
  if (CarpublicKey.isEmpty()) {
    Serial.println("Public key is empty");
    return;
  }

  // Split the public key into chunks and publish each chunk with metadata
  size_t total_chunks = (CarpublicKey.length() + CHUNK_SIZE - 1) / CHUNK_SIZE;
  for (size_t i = 0; i < total_chunks; ++i) {
    String chunk = CarpublicKey.substring(i * CHUNK_SIZE, (i + 1) * CHUNK_SIZE);
    String message_with_metadata = String(car_id) + "/" + String(i + 1) + "/" + String(total_chunks) + ":" + chunk;
    
    client.publish(pub_key_topic, message_with_metadata.c_str());
    delay(100); // Small delay to ensure proper sending
  }
}

void encryptAndPublish(const char* message) {
  String publicKey = readKey("/public_key.pem");
  if (publicKey.isEmpty()) {
    Serial.println("Public key is empty");
    return;
  }

  mbedtls_pk_context pk;
  mbedtls_pk_init(&pk);

  if (mbedtls_pk_parse_public_key(&pk, (const unsigned char*)publicKey.c_str(), publicKey.length() + 1) != 0) {
    Serial.println("Failed to parse public key");
    return;
  }

  Serial.print("Plaintext message: ");
  Serial.println(message);

  unsigned char encrypted[512];
  size_t olen;
  mbedtls_entropy_context entropy;
  mbedtls_ctr_drbg_context ctr_drbg;

  mbedtls_entropy_init(&entropy);
  mbedtls_ctr_drbg_init(&ctr_drbg);

  const char *pers = "rsa_encrypt";
  mbedtls_ctr_drbg_seed(&ctr_drbg, mbedtls_entropy_func, &entropy, (const unsigned char *) pers, strlen(pers));

  mbedtls_rsa_context* rsa = mbedtls_pk_rsa(pk);
  mbedtls_rsa_set_padding(rsa, MBEDTLS_RSA_PKCS_V21, MBEDTLS_MD_SHA256);  // Use OAEP with SHA-256 for encryption

  int ret = mbedtls_rsa_rsaes_oaep_encrypt(rsa, mbedtls_ctr_drbg_random, &ctr_drbg, MBEDTLS_RSA_PUBLIC, NULL, 0, strlen(message), (const unsigned char*)message, encrypted);
  if (ret != 0) {
    Serial.print("Encryption failed, error code: ");
    Serial.println(ret);
    return;
  }

  unsigned char encoded[512];
  size_t encoded_len;
  if (mbedtls_base64_encode(encoded, sizeof(encoded), &encoded_len, encrypted, rsa->len) != 0) {
    Serial.println("Base64 encoding failed");
    return;
  }


  // Ensure we are connected before publishing
  if (!client.connected()) {
    reconnect();
  }

  // Split the encrypted data into chunks and publish each chunk with metadata
  size_t data_chunks = 3; // First 3 chunks for data

  // Publish data chunks
  for (size_t i = 0; i < data_chunks; ++i) {
    char chunk[CHUNK_SIZE + 1];
    strncpy(chunk, (char*)encoded + i * CHUNK_SIZE, CHUNK_SIZE);
    chunk[CHUNK_SIZE] = '\0';
    
    char message_with_metadata[CHUNK_SIZE + 50];
    snprintf(message_with_metadata, sizeof(message_with_metadata), "%s/data/%zu/%zu:%s", car_id, i + 1, data_chunks, chunk);
    client.publish(pub_topic, message_with_metadata);
    delay(100); // Small delay to ensure proper sending
  }

  mbedtls_pk_free(&pk);
  mbedtls_entropy_free(&entropy);
  mbedtls_ctr_drbg_free(&ctr_drbg);
}

void decryptMessage(const String& encryptedBase64, const String& privateKey) {
    mbedtls_pk_context pk;
    mbedtls_pk_init(&pk);

    if (mbedtls_pk_parse_key(&pk, (const unsigned char*)privateKey.c_str(), privateKey.length() + 1, NULL, 0) != 0) {
        Serial.println("Failed to parse private key");
        return;
    }

    unsigned char encrypted[512];
    size_t encrypted_len = encryptedBase64.length();
    unsigned char decoded[512];
    size_t decoded_len;

    if (mbedtls_base64_decode(decoded, sizeof(decoded), &decoded_len, (const unsigned char*)encryptedBase64.c_str(), encrypted_len) != 0) {
        Serial.println("Base64 decoding failed");
        return;
    }

    unsigned char decrypted[512];
    size_t decrypted_len = 0;
    mbedtls_rsa_context* rsa = mbedtls_pk_rsa(pk);
    mbedtls_rsa_set_padding(rsa, MBEDTLS_RSA_PKCS_V21, MBEDTLS_MD_SHA256);

    mbedtls_ctr_drbg_context ctr_drbg;
    mbedtls_ctr_drbg_init(&ctr_drbg);

    mbedtls_entropy_context entropy;
    mbedtls_entropy_init(&entropy);

    const char *pers = "rsa_decrypt";
    if (mbedtls_ctr_drbg_seed(&ctr_drbg, mbedtls_entropy_func, &entropy, (const unsigned char*)pers, strlen(pers)) != 0) {
        Serial.println("Failed to initialize RNG");
        return;
    }

    if (mbedtls_rsa_pkcs1_decrypt(rsa, mbedtls_ctr_drbg_random, &ctr_drbg, MBEDTLS_RSA_PRIVATE, &decoded_len, decoded, decrypted, sizeof(decrypted)) != 0) {
        Serial.println("Decryption failed");
        return;
    }

    Serial.print("Decrypted message: ");
    Serial.println((char*)decrypted);
    // Parse the JSON decrypted message
    DynamicJsonDocument doc(512);
    DeserializationError error = deserializeJson(doc, (char*)decrypted);
    if (error) {
        Serial.print("JSON deserialization failed: ");
        Serial.println(error.c_str());
        return;
    }

    // Handle different events
    const char* event = doc["event"];
    if (strcmp(event, "hardBraking") == 0) {
        
        // Handle hardBraking event
        Serial.println("Handling hardBraking event");
        
    } else if (strcmp(event, "overtaking_request") == 0) {
        
        /* Sending 'G' to the stm32 */
        SerialPort.write('G');
        SerialPort.write('G');

        // Handle overtaking_request event
        Serial.println("Handling overtaking_request event");
  
    } else if (strcmp(event, "Dim_Light") == 0) {
        
        //Send 'L' to STM32 if hard braking detected
        SerialPort.write('L');
        SerialPort.write('L');

        Serial.println("Handling Dim_Light event");
      
    } else {
        Serial.println("Unknown event");
    }
    mbedtls_pk_free(&pk);
    mbedtls_ctr_drbg_free(&ctr_drbg);
    mbedtls_entropy_free(&entropy);
}


void publishData() {
  if (!client.connected()) {
    reconnect();
  }

  String payload = "{\"gpsLocation\": \"" + (Global_fGPS_Latitude) + "," + (Global_fGPS_Longitude) + "\", \"speed\": " + (Global_uint16Speed) +
                   ", \"overtaking_request\": " + overtaking_request +
                   ", \"overtaking_response\": " + overtaking_response +
                   ", \"overtaking_action\": " + overtaking_action +
                   ", \"Dim_Light\": " + dimLights_detect +
                   ", \"hardBraking\": " + hardBraking_alert + "}";


  encryptAndPublish(payload.c_str());

  // Reset the flags after sending to the server
  hardBraking_alert = false;
  overtaking_response = false;
  overtaking_action = false;
  publish_Ready = false;
}

void callback(char* topic, byte* payload, unsigned int length) {
  String chunk = String((char*)payload).substring(0, length);

  // Extract the chunk metadata and the chunk data
  int sep = chunk.indexOf(':');
  String chunkInfo = chunk.substring(0, sep);
  String chunkData = chunk.substring(sep + 1);

  // Extract metadata: car_id/data/chunkIndex/totalChunks
  int firstSlash = chunkInfo.indexOf('/');
  int secondSlash = chunkInfo.indexOf('/', firstSlash + 1);
  int thirdSlash = chunkInfo.indexOf('/', secondSlash + 1);

  int chunkIndex = chunkInfo.substring(secondSlash + 1, thirdSlash).toInt();
  totalChunks = chunkInfo.substring(thirdSlash + 1).toInt();

  if (chunkIndex <= MAX_CHUNKS) {
    receivedChunks[chunkIndex - 1] = chunkData;
    receivedCount++;

    if (receivedCount == totalChunks) {
      // Join all chunks
      String encryptedBase64;
      for (int i = 0; i < totalChunks; i++) {
        encryptedBase64 += receivedChunks[i];
      }


      // Read private key
      String privateKey = readKey("/car2_private_key.pem");

      if (!privateKey.isEmpty()) {
        decryptMessage(encryptedBase64, privateKey);
      }

      // Reset for next message
      receivedCount = 0;
      totalChunks = 0;
    }
  } else {
    Serial.println("Error: chunkIndex exceeds MAX_CHUNKS");
  }
}
