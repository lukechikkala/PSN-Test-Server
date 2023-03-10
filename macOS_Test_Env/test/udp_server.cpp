#include <sys/types.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include <string>

#include <chrono>
#include <thread>

#include <unistd.h>

#include <sys/socket.h>
#include <iostream>
#include <sstream>

#define PORT 56565

void title()
{
	system("clear");
	std::cout << "\t┌───────────────────────────────┐" << std::endl;
	std::cout << "\t│\tSOCKET PROGRAMMING\t│" << std::endl;
	std::cout << "\t│		   by luke\t│" << std::endl;
	std::cout << "\t└───────────────────────────────┘" << std::endl;
}

int main()
{
	int i = 1 ;
	uint64_t timestamp = 0 ;

	title();

	// SERVER
	struct sockaddr_in add_LC = { 
		.sin_family = AF_INET,				// IPv4
		.sin_addr.s_addr = INADDR_ANY,		// Available address
		.sin_port = htons(PORT)				// Setting port to 5000
	};

	int option = 1;
	int saddrSize = sizeof(add_LC);
	int socketServer = socket(AF_INET, SOCK_DGRAM, 0);	// SOCK_STREAM is for TCP and SOCK_DGRAM is for UDP
	setsockopt(socketServer, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &option, sizeof(option));
	const std::string message = "Hello World" ;

	if (socketServer == -1)
	{
		std::cerr << "!!!! Unable to create socket !!!!" << std::endl;
		return -1;
	}
	while( true )
	{
		if ( timestamp % 16 )
		{
			sendto( socketServer, message.c_str(), (int)message.length(), 0, reinterpret_cast<sockaddr *>( &add_LC ), sizeof( add_LC ) ) ;
			// std::cout << "\rMessage(s) Sent: " << i;
			std::cout << "Message : " << "\r" << i ;
			i++ ;
		}
		timestamp++;
		std::this_thread::sleep_for(std::chrono::milliseconds( 5 ));
	}
}