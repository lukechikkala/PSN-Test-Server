/*
	Author: Luke Chikkala
	Email: LukeChikkala@gmail.com

	This is not the original PSN Server application built by VYV and MA Lighting.
	This server is purely for testing purposes.
	The conventions in the scripts are not standard at the moment.
	This is because I'm learning how to handle real-world socket programming as
	I'm building this open source project.
	It comes with no guarantee that it works exactly as expected and as specified
	by the PSN group.
*/

#include "PSN_Test_Server.hpp"

int main( void )
{
	system("clear") ;
	int i = 1;
	int DataPacketCounter = 0;
	int InfoPacketCounter = 1;
    //============================================================================================================================================================
	// Session ???
    //============================================================================================================================================================

    //============================================================================================================================================================
    // Init server
    //============================================================================================================================================================
    udp_socket socket_server ;
    socket_server.enable_send_message_multicast() ;

	std::string ServerName  = "Test PSN Server by Luke Chikkala";
	std::string TrackerName = "LC_Tracker";

    ::psn::psn_encoder psn_encoder( ServerName ) ;
    ::psn::tracker_map Tracker_LC ;

	Tracker_LC[ 0 ] = ::psn::tracker( 0, TrackerName ) ;

    float orbit = 88.0f ;
	float a ;
	float b ;
	float x ;
	float cb ;
	float sb ;
	uint64_t timestamp = 0 ;

    //============================================================================================================================================================
	// Title
    //============================================================================================================================================================
    std::cout << "\n";
    std::cout << "  /#######   /######  /##   /##        /######                                                        " << std::endl;
    std::cout << " | ##__  ## /##__  ##| ### | ##       /##__  ##                                                       " << std::endl;
    std::cout << " | ##  \\ ##| ##  \\__/| ####| ##      | ##  \\__/  /######   /######  /##    /## /######   /######   " << std::endl;
    std::cout << " | #######/|  ###### | ## ## ##      |  ######  /##__  ## /##__  ##|  ##  /##//##__  ## /##__  ##     " << std::endl;
    std::cout << " | ##____/  \\____  ##| ##  ####       \\____  ##| ########| ##  \\__/ \\  ##/##/| ########| ##  \\__/" << std::endl;
    std::cout << " | ##       /##  \\ ##| ##\\  ###       /##  \\ ##| ##_____/| ##        \\  ###/ | ##_____/| ##       " << std::endl;
    std::cout << " | ##      |  ######/| ## \\  ##      |  ######/|  #######| ##         \\  #/  |  #######| ##         " << std::endl;
    std::cout << " |__/       \\______/ |__/  \\__/       \\______/  \\_______/|__/          \\_/    \\_______/|__/     " << std::endl;

    std::cout << " ________________________________________________________________________________________________\n" << std::endl;

    std::cout << " Server Name      : " << ServerName << std::endl;
    std::cout << " Tracker Name     : " << TrackerName << std::endl;
	socket_server.GetIP_LC( ::psn::DEFAULT_UDP_MULTICAST_ADDR, ::psn::DEFAULT_UDP_PORT );

    std::cout << " ________________________________________________________________________________________________" << std::endl;

    std::cout << "\n  DATA      INFO          X              Y" << std::endl;
    //============================================================================================================================================================
    // Main loop
    //============================================================================================================================================================
    while ( true ) 
    {
		//============================================================================================================================================================
		// Update Values
		//============================================================================================================================================================
		a	= 1.0f / orbit ;
		b	= 0.5f ;
		x	= ( float )timestamp ;
		cb	= ::std::cosf( a * x ) * b ;
		sb	= ::std::sinf( a * x ) * b ;
		Tracker_LC[ 0 ].set_pos( ::psn::float3( sb, cb, 0 ) ) ;

		std::this_thread::sleep_for(std::chrono::milliseconds( 1 ));
		//============================================================================================================================================================
		// Send DATA
		//============================================================================================================================================================
        if ( timestamp % 16 == 0 ) // transmit data at 60 Hz approx.
        {
            ::std::list< ::std::string > data_packets = psn_encoder.encode_data( Tracker_LC , timestamp ) ;
            for ( auto it = data_packets.begin() ; it != data_packets.end() ; ++it )
            {
                    socket_server.send_message( ::psn::DEFAULT_UDP_MULTICAST_ADDR , ::psn::DEFAULT_UDP_PORT , *it ) ;
					DataPacketCounter++ ;
					std::cout << "\r"
								<< std::setw(7)
								<< std::setfill(' ')
								<< DataPacketCounter
								<< std::setw(10) << InfoPacketCounter
								<< std::setw(15) << sb
								<< std::setw(15) << cb
								<< std::flush;
            }

       }

		//============================================================================================================================================================
		// Send INFO
		//============================================================================================================================================================
        if ( timestamp % 1000 == 0 ) // transmit info at 1 Hz approx.
        {
            ::std::list< ::std::string > info_packets = psn_encoder.encode_info( Tracker_LC , timestamp ) ;
            for ( auto it = info_packets.begin() ; it != info_packets.end() ; ++it )
			{
                socket_server.send_message( ::psn::DEFAULT_UDP_MULTICAST_ADDR , ::psn::DEFAULT_UDP_PORT , *it ) ;
				InfoPacketCounter++;
			}
        }
        timestamp++ ; i++ ;
    }
}