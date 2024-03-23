import socket

# Create a TCP/IP socket
server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# Bind the socket to the address and port
server_address = ('localhost', 8888) # 22 for ssh 
server_socket.bind(server_address)

# Listen for incoming connections
server_socket.listen(5)

print("Server is listening...")

while True:
    # Wait for a connection
    client_socket, client_address = server_socket.accept()
    
    try:
        print("Connection from", client_address)
        
        # Receive data from the client
        data = client_socket.recv(1024)
        print("Received:", data.decode())
        
        # Send a response back to the client
        client_socket.sendall(b"Hello from the server!")

    finally:
        # Clean up the connection
        client_socket.close()

