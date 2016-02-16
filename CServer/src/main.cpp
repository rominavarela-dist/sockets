#include <cstdlib>//legacy stdlib.h and time.h
#include <iostream>
#include <strings.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>

#include "struct.h"

using namespace std;

int serverPort;
int serverSocket= -1;
struct sockaddr_in serverAddress;

int clientSocket= -1;
struct sockaddr_in clientAddress;
socklen_t clientLen;

/**
* @method main
**/
int main(int argc, const char* argv[])
{
	try
	{
			// load configuration
			if(argc != 2)
				throw("Run with argument <port>");
			serverPort = atoi(argv[1]);

			// connect
			serverSocket = socket(AF_INET, SOCK_STREAM, 0);
			if(serverSocket <0)
				throw("Could not open socket");

			bzero((char *) &serverAddress, sizeof(serverAddress));
			serverAddress.sin_family = AF_INET;
			serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
			serverAddress.sin_port = htons(serverPort);
			if( bind(serverSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) <0 )
				throw("Could not bind socket");

			listen(serverSocket, 1);
			std::cout << "[SERVER] Server listening at port  " << serverPort << endl;

			clientLen = sizeof(clientAddress);
			clientSocket = accept(serverSocket,(struct sockaddr *) &clientAddress, &clientLen);
			if(clientSocket <0)
				throw("Could not connect to client");

			// listen request
			Struct req;
			read(clientSocket, &req, sizeof(req));
			std::cout << "[SERVER] Request:" << endl;
			std::cout << "[ \n    x: " << req.x <<
					 ",\n    y: " << req.y <<
					 ",\n    z: " << req.z <<
					 "\n]" << endl;

			// send response
 			Struct res;
 			res.x = req.x + 1;
 			res.y = req.y + 1.0;
 			res.z = req.z + 1;
 			write (clientSocket, (void *)&res, sizeof(res));
 			std::cout << "[SERVER] Response:" << endl;
 			std::cout << "[ \n    x: " << res.x <<
 					 ",\n    y: " << res.y <<
 					 ",\n    z: " << res.z <<
 					 "\n]" << endl;

			std::cout << "[SERVER] Done" << endl;
	}
	catch(const char* msg)
	{
			std::cout << "[ERROR] " << msg << endl;
	}

	// finally
	if(clientSocket > -1)
	{
		close(clientSocket);
		std::cout << "[SERVER] Client socket closed" << endl;
	}

	if(serverSocket > -1)
	{
		close(serverSocket);
		std::cout << "[SERVER] Server socket closed" << endl;
	}

	std::cout << "[SERVER] Server down" << endl;

	return 0;
}
