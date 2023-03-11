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
#include <sys/ioctl.h>
#include <iostream>
#include <sstream>
#include <iomanip>

class udp_socket
{
public :
	udp_socket( void )
	{
		socket_ = socket( AF_INET , SOCK_DGRAM , IPPROTO_UDP ) ;
		u_long arg = 1 ;
		ioctl( socket_ , FIONBIO , &arg ) ;
	}
	~udp_socket( void )
	{
		std::cout << "~udp_socket() called :-)" << std::endl ; 
	}

	void GetIP_LC( const std::string &address , unsigned short port )
	{
		sockaddr_in add ;
		add.sin_family = AF_INET ;
		inet_pton( AF_INET , address.c_str() , &add.sin_addr.s_addr ) ;
		add.sin_port = htons( port ) ;

		std::cout << " Destination IP   : " << address.c_str() << std::endl;
		std::cout << " Destination Port : " << port << std::endl;
	}

	bool send_message( const std::string &address , unsigned short port , const::std::string &message )
	{
		sockaddr_in add ;
		add.sin_family = AF_INET ;
		inet_pton( AF_INET , address.c_str() , &add.sin_addr.s_addr ) ;
		add.sin_port = htons( port ) ;

		if( sendto( socket_ , message.c_str() , (int)message.length() , 0 , reinterpret_cast<sockaddr*>( &add ) , sizeof( add ) ) > 0 )
			return true ;

		return false ;
	}

	bool enable_send_message_multicast( void )
	{
		struct in_addr add ;
		add.s_addr = INADDR_ANY ;

		int result = setsockopt( socket_ ,
								 IPPROTO_IP ,
								 IP_MULTICAST_IF ,
								 (const char *)&add ,
								 sizeof( add ) ) ;
		return ( result != SO_ERROR ) ;
	}
private :
	unsigned int socket_ ;
} ;