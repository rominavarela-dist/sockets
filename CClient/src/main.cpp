#include <cstdlib>//legacy stdlib.h and time.h
#include <iostream>
#include <ctime>
#include <strings.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>

#include "struct.h"

using namespace std;

const char* serverAddr;
int serverPort;
int clientSocket= -1;
struct sockaddr_in clientAddress;

/**
* @method main
**/
int main(int argc, const char* argv[])
{
	try
	{
			// load configuration
			if(argc != 3)
				throw("Run with arguments <clientAddress> <port>");
			serverAddr = argv[1];
			serverPort = atoi(argv[2]);
			std::cout << "[CLIENT] Connecting to " << serverAddr << ":" << serverPort << endl;

			// connect
			clientSocket = socket(AF_INET, SOCK_STREAM, 0);
			if(clientSocket <0)
				throw("Could not open socket");

			bzero((char *) &clientAddress, sizeof(clientAddress));
			clientAddress.sin_family = AF_INET;
			clientAddress.sin_addr.s_addr = inet_addr(serverAddr);
			clientAddress.sin_port = htons(serverPort);
			if(connect(clientSocket, (struct sockaddr *)&clientAddress, sizeof(clientAddress)) == -1)
				throw("Connection refused");

			std::cout << "[CLIENT] Connection started" << endl;

			// send request
			Struct req;
			srand(clock());//init rand
			req.x = rand() % 100;
			req.y = 1.5;
			req.z = char((rand() % 26) + 65);
			write (clientSocket, (void *)&req, sizeof(req));
			std::cout << "[CLIENT] Request:" << endl;
			std::cout << "[ \n    x: " << req.x <<
					 ",\n    y: " << req.y <<
					 ",\n    z: " << req.z <<
					 "\n]" << endl;

			// listen response
 			Struct res;
 			read(clientSocket, &res, sizeof(res));
 			std::cout << "[CLIENT] Response:" << endl;
 			std::cout << "[ \n    x: " << res.x <<
 					 ",\n    y: " << res.y <<
 					 ",\n    z: " << res.z <<
 					 "\n]" << endl;
 			std::cout << "[CLIENT] Done" << endl;

			std::cout << "[CLIENT] Done" << endl;
	}
	catch(const char* msg)
	{
			std::cout << "[ERROR] " << msg << endl;
	}

	// finally
	if(clientSocket > -1)
	{
		close(clientSocket);
		std::cout << "[CLIENT] Client socket closed" << endl;
	}

	std::cout << "[CLIENT] Client down" << endl;

	return 0;
}
