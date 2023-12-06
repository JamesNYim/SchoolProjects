import argparse
import os
import sys
import time
import socket
import csv

#Initializing the parser
parser = argparse.ArgumentParser(description='Argument Parser')
parser.add_argument('-p', "--Port", type = int)
parser.add_argument('-d', "--Directory", type = str)
args = parser.parse_args()

portNum = args.Port
filePath = args.Directory

ipAdd = "127.0.0.1"
httpFileName = "jnyimHTTPResponses.txt"
csvFileName = "jnyimSocketOutput.csv"

#Mime Types
mimeTypes = {".csv": "text/csv", 
	     	"doc": "application/msword",
			"docx": "application/vnd.openxmlformats-officedocument.wordprocessingml.document",
			"gif": "image/gif",
			"htm": "text/html",
			"html": "text/html",
			"jpeg": "image/jpeg",
			"jpg": "image/jpeg",
			"png": "image/png",
			"txt": "text/plain",
			"zip": "application/zip",
			"pdf": "application/pdf"}

# Checking if file directory exists
if (not os.path.exists(filePath)):
	print(f"<{filePath}> does not exist", file=sys.stderr)
	exit()

# Checking for valid port number
portType = [False, False] #portType[0] checks if its a well known port
						  #portType[1] checks if its a valid port

# Checking if the inputted port is a well known port
if (0 <= portNum and portNum <= 1023):
	portType[0] = True
	portType[1] = True

elif (1024 <= portNum and portNum <= 65535):
	portType[1] = True

# Printing Port Number Warning
if (not portType[1]):
	print("Port number: " + str(portNum) + " is not a valid port number", file=sys.stderr)
	exit()

elif (portType[0]):
	print("[WARNING] Port Number: " + str(portNum) + " is a well known port number") #file=sys.stderr

# Opening Socket
serverSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM) 
serverSocket.bind((ipAdd, portNum))
print("Welcome socket created: <" + str(ipAdd) + ">, <" + str(portNum) + ">") 
serverSocket.listen(5) #Queue of msgs

#Waitng for msgs and sending
print("[LISTENING...]")
while True:

	# Accepting connection from client request
	clientSocket, clientAddr = serverSocket.accept()
	print("Connection Requested from " + str(clientAddr))
	
	# Getting Client Request and processing it
	requestMsg = clientSocket.recv(1024).decode() # Getting request message
	print(requestMsg)
	filePath += requestMsg.split()[1] # Getting file name from request message
	httpVer = requestMsg.split()[2]
	httpMethod = requestMsg.split()[0]

	# Forming a HTTP Header & Response
	httpHeader = ""
	contentType = "application/octet-stream"

	if (not (httpVer == "HTTP/1.1")): # Checking the HTTP Version
		httpHeader += "HTTP/1.1 505 HTTP Version Not Supported\r\n\r\n"
		clientSocket.send(httpHeader.encode())

		# Writing to CSV
		with open(csvFileName, "a") as csvFile:
			csvWriter = csv.writer(csvFile)

			csvWriter.writerow(["Client request served", 
		       "4-Tuple:", ipAdd, portNum, clientAddr[0], clientAddr[1], 
			   "Requested URL", filePath, "HTTP/1.1 505 HTTP Version Not Supported", 
			   "Bytes transmitted:", 0])
		
		httpHeader += "Date: " + time.strftime("%a, %d %b %Y %I:%M:%S GMT", time.gmtime())
		
	elif (not (httpMethod == "GET")): # Checking the HTTP Method
		httpHeader += "HTTP/1.1 501 Not Implented\r\n\r\n"
		clientSocket.send(httpHeader.encode())

		# Writing to CSV
		with open(csvFileName, "a") as csvFile:
			csvWriter = csv.writer(csvFile)

			csvWriter.writerow(["Client request served", 
		       "4-Tuple:", ipAdd, portNum, clientAddr[0], clientAddr[1], 
			   "Requested URL", filePath, "HTTP/1.1 501 Not Implented", 
			   "Bytes transmitted:", 0])

		httpHeader += "Date: " + time.strftime("%a, %d %b %Y %I:%M:%S GMT", time.gmtime())
	
	elif (not os.path.exists(filePath)): # Checking if the file exists
		httpHeader += "HTTP/1.1 404 Not Found\r\n\r\n"
		clientSocket.send(httpHeader.encode()) 
		
		# Writing to CSV
		with open(csvFileName, "a") as csvFile:
			csvWriter = csv.writer(csvFile)

			csvWriter.writerow(["Client request served", 
		       "4-Tuple:", ipAdd, portNum, clientAddr[0], clientAddr[1], 
			   "Requested URL", filePath, "HTTP/1.1 404 Not Found", 
			   "Bytes transmitted:", 0])
			
		httpHeader += "Date: " + time.strftime("%a, %d %b %Y %I:%M:%S GMT", time.gmtime())
		
	else: # Sending the File Requested 

		# Forming 200 OK Header & Sending
		httpHeader  += "HTTP/1.1 200 OK\r\n\r\n"
		clientSocket.send(httpHeader.encode())

		# Writing to CSV
		with open(csvFileName, "a") as csvFile:
			csvWriter = csv.writer(csvFile)

			csvWriter.writerow(["Client request served", 
		       "4-Tuple:", ipAdd, portNum, clientAddr[0], clientAddr[1], 
			   "Requested URL", filePath, "HTTP/1.1 200 OK", 
			   "Bytes transmitted:", os.path.getsize(filePath)])
		
		# Writing the rest of the http header
		print(filePath)
		mimeType = filePath.split(".")[2]
		httpHeader += f"Content-Type: {mimeTypes[mimeType]}\n"
		httpHeader += f"Content-Length: {os.path.getsize(filePath)}\n"
		httpHeader += "Date: " + time.strftime("%a, %d %b %Y %I:%M:%S GMT\n", time.gmtime())
		httpHeader += "Last-Modified: " + time.strftime("%a, %d %b %Y %I:%M:%S GMT\n", time.gmtime(os.path.getmtime(filePath)))
		
		# Reading and sending the File
		BUFFER_SIZE = 1024
		file = open(filePath, "rb") # Opening the file
		bytesBuffer = file.read(BUFFER_SIZE) #Inital read
		while (bytesBuffer):
			clientSocket.send(bytesBuffer)
			bytesBuffer = file.read(BUFFER_SIZE)

	file.close()
	clientSocket.close()
	
	#Writing HTTP response to file
	if (not os.path.exists(httpFileName)):
		print(f"{httpFileName} is not a valid file path", file=sys.stderr)
		exit()
	else:
		httpFile = open(httpFileName, "w")
		print(httpHeader)
		httpFile.write(httpHeader)
		httpFile.close()	
	exit()	
	








