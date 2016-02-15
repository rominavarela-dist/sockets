#include <iostream>
#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <cstdlib>

#include "struct.h"

using namespace std;

const char* serverAddr;
int serverPort;
int sockfd;//socket file descriptor
struct sockaddr_in address;//ipv4 address

/**
* @method main
**/
int main(int argc, const char* argv[])
{

	// load configuration
	std::cout << argc << endl;
	if(argc != 3)
	{
		std::cout << "[CLIENT] Error. Run with arguments <address> <port>" << endl;
		exit(1);
	}
	serverAddr = argv[1];
	serverPort = atoi(argv[2]);
	std::cout << "[CLIENT] Connecting to " << serverAddr << ":" << serverPort << endl;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = inet_addr(serverAddr);
	address.sin_port = htons(serverPort);

	// connect
	if(connect(sockfd, (struct sockaddr *)&address, sizeof(address)) == -1)
	{
		std::cout << "[CLIENT] Connection refused" << endl;
		exit(1);
	}
	std::cout << "[CLIENT] Connection started" << endl;

	// send request
	Struct req;
	req.x = 1;
	req.y = 5.0;
	req.z = 'c';
	write (sockfd, (void *)&req, sizeof(req));
	std::cout << "[CLIENT] Request:" << endl;
	std::cout << "[ \n    x: " << req.x <<
			 ",\n    y: " << req.y <<
			 ",\n    z: " << req.z <<
			 "\n]" << endl;

	// listen response
	Struct res;
	read(sockfd, &res, sizeof(res));
	std::cout << "[CLIENT] Response:" << endl;
	std::cout << "[ \n    x: " << res.x <<
			 ",\n    y: " << res.y <<
			 ",\n    z: " << res.z <<
			 "\n]" << endl;
	std::cout << "[CLIENT] Done" << endl;

	close(sockfd);

	std::cout << "[CLIENT] Connection closed" << endl;
	std::cout << "[CLIENT] Client down" << endl;

	return 0;
}
