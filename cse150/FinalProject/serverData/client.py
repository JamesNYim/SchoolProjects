import socket
import argparse

#Initializing the parser
parser = argparse.ArgumentParser(description='Argument Parser')
parser.add_argument('-p', "--Port", type = int)
parser.add_argument('-a', "--ipAddress", type = str)
args = parser.parse_args()
portNum = args.Port
ipAddress = args.ipAddress

#Opening the port to request and recieve
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((ipAddress, portNum))

fullMsg = ''
while True:
    msg = s.recv(8)
    if len(msg) <= 0:
        break
    fullMsg += msg.decode()
print(fullMsg)
s.close()