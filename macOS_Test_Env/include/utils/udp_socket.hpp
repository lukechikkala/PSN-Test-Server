/*
	Author: Luke Chikkala
	UDP Socket Class
*/

#include <sys/types.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include <string>

#include <unistd.h>

#include <sys/socket.h>
#include <iostream>
#include <sstream>
#include <iomanip>

class udp_socket
{
public :
	udp_socket()
	{
		// ::LC:: UDP Socket for UNIX
		struct sockaddr_in saddr = {
			.sin_family = AF_INET,
			.sin_addr.s_addr = INADDR_ANY,
			.sin_port = htons( 56565 )
		};

		int option = 1;
		int saddrSize = sizeof( saddr );
		int socketServer = socket( AF_INET, SOCK_DGRAM, IPPROTO_UDP );
		setsockopt(
			socketServer,
			SOL_SOCKET,
			SO_REUSEADDR | SO_REUSEPORT,
			&option,
			sizeof( option )
			);
		
		if( socketServer == -1 )
			std::cerr << " !!  UNABLE TO CREATE SOCKET !! " << std::endl;
	}

	~udp_socket( void ){}

	void GetIP_LC( const std::string & address, unsigned short port )
	{
		sockaddr_in add;
		add.sin_family = AF_INET;
		inet_pton( AF_INET, address.c_str(), &add.sin_addr.s_addr );
		add.sin_port = htons( port );

		std::cout << " Destination IP   : " << address.c_str() << std::endl;
		std::cout << " Destination Port : " << port << std::endl;
	}

	// bool send_message( const std::string & address , unsigned short port , const ::std::string & message )
    // {
	// 	struct sockaddr_in add = {
	// 		 .sin_family		= AF_INET
	// 		// ,.sin_addr.s_addr	= INADDR_ANY
	// 		,.sin_port			= htons( port )
	// 	} ;
	// 	inet_pton( AF_INET, address.c_str(), &add.sin_addr.s_addr ) ;

	// 	int option = 1 ;
	// 	int saddrSize = sizeof( add ) ;
	// 	int socketServer = socket( AF_INET, SOCK_DGRAM, 0 ) ;

	// 	if ( sendto( socketServer , message.c_str() , (int)message.length() , 0 , reinterpret_cast<sockaddr *>( &add ) , sizeof( add ) ) )
	// 		return true ;

	// 	return false ;
    // }

	// bool enable_send_message_multicast( void ) 
	// {
		
	// 	struct in_addr add ;
	// 	add.s_addr = INADDR_ANY ;

	// 	int result = setsockopt( socketServer , 
	// 					   IPPROTO_IP , 
	// 					   IP_MULTICAST_IF , 
	// 					   (const char*)&add , 
	// 					   sizeof( add ) ) ;
	// 	return ( result != SO_ERROR ) ; 
	// }

	bool send_message( const std::string & address , unsigned short port , const ::std::string & message )
    {
        sockaddr_in add ;
        add.sin_family = AF_INET ;
        inet_pton( AF_INET , address.c_str() , &add.sin_addr.s_addr ) ;
        add.sin_port = htons( port ) ;
        
		if ( sendto( socketServer , message.c_str() , (int)message.length() , 0 , reinterpret_cast<sockaddr *>( &add ) , sizeof( add ) ) > 0 )
			return true ;

		return false ;
    }

	bool enable_send_message_multicast( void ) 
	{
		struct in_addr add ;
		add.s_addr = INADDR_ANY ;

		int result = setsockopt( socketServer , 
						IPPROTO_IP , 
						IP_MULTICAST_IF , 
						(const char*)&add , 
						sizeof( add ) ) ;
		return ( result != SO_ERROR ) ; 
	}

private :
	unsigned int socketServer ;
};