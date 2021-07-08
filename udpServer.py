#!/usr/bin/python3

import socket

ip = "127.0.0.1"
port = 6000
buffer = 1024
run = True

serverUDPSocket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
serverUDPSocket.bind((ip, port))

while run:
    (infoFromClient, addr) = serverUDPSocket.recvfrom(buffer)
    receivedMessage = infoFromClient.decode()
    if not receivedMessage:
        print("Something is wrong. Not receiving information from client")
    elif receivedMessage == "exit":
        print ("Server exit the program") 
        serverUDPSocket.sendto("Server exit the program".encode(), addr)
        run = False
    else:
        print("From client:", receivedMessage)
        print("From address:", addr)
        serverUDPSocket.sendto(receivedMessage.upper().encode(), addr)
