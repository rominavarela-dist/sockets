#include <iostream>
#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>


#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstdlib>
#include <iostream>
#include <pthread.h>

using namespace std;

const char* serverAddr= "10.0.1.110";
const int serverPort= 9000;

int sockfd;//socket file descriptor
struct sockaddr_in address;//ipv4 address

struct Struct
{
	int x;
	float y;
	char z;
};

/**
* @method main
**/
int main(int argc, char* argv[])
{

	// load configuration
	std::cout << "Hello World!" << endl;
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
