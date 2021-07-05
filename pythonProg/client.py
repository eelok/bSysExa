#!/usr/bin/python3

import socket

ip = "127.0.0.1"
port = 6000
buffer = 1024
run = True

clientUDPSocket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

while run:
    message = input("Insert message to server:=>")
    clientUDPSocket.sendto(message.encode(), (ip, port))
    (data, addr) = clientUDPSocket.recvfrom(buffer)
    messageFromServer = data.decode()
    if messageFromServer != "Server exit the program":
        print("From Server", messageFromServer)
        print("From address", addr)
    else:
        print("Client exit program")
        run = False    
