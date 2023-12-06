import argparse
import os
import sys
import time


#Initializing the parser
parser = argparse.ArgumentParser(description='Argument Parser')
parser.add_argument('-p', "--Port", type = int)
parser.add_argument('-d', "--FilePath", type = str)

args = parser.parse_args()

portNum = args.Port
filePath = args.FilePath

# Checking for valid port number
portType = [False, False] #portType[0] checks if its a well known port
						  #portType[1] checks if its a valid port

# Checking if the inputted port is a well known port
if (0 <= portNum and portNum <= 1023):
	portType[0] = True
	portType[1] = True

elif (1024 <= portNum and portNum <= 65535):
	portType[1] = True

# Checking if the inputted file path is valid
validPath = False
if (os.path.exists(filePath)):
	validPath = True

# Printing out to stdout

# Printing Port Number Warning
if (not portType[1]):
	print("Port number: " + str(portNum) + " is not a valid port number", file=sys.stderr)
	exit()

elif (portType[0]):
	print("[WARNING] Port Number: " + str(portNum) + " is a well known port number") #file=sys.stderr

# Printing stdout info
print("<Port>: " + str(portNum) + " , <Root Directory>: " + filePath, file=sys.stdout)

# Getting File Size
fileSize = os.path.getsize(filePath)

# Printing Header

print(str(portNum) + ": entered port number")
print(filePath + ": entered root directory path")
print("HTTP/1.1 200 OK")
print("Content-Type: text/html")
print("Content-Length: " + str(fileSize))
print("Date: " + time.strftime("%a, %d %b %Y %I:%M:%S GMT", time.gmtime()))
print("Last-Modified: " + time.strftime("%a, %d %b %Y %I:%M:%S GMT", time.gmtime(os.path.getmtime(filePath))))
print("\n")

# Printing File
file = open(filePath, "r")
print(file.read())








