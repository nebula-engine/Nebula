#include <cstdlib>
#include <deque>
#include <iostream>
#include <thread>

#include <netinet/in.h>
#include <sys/types.h>       // For data types
#include <sys/socket.h>      // For socket(), connect(), send(), and recv()
#include <netdb.h>           // For gethostbyname()
#include <arpa/inet.h>       // For inet_addr()
#include <unistd.h>          // For close()
#include <netinet/in.h>      // For sockaddr_in

#include <gal/net/client.hpp>

//#include <galaxy/config.hpp>
//#include <galaxy/free.hpp>

void fillAddr(char const * address, unsigned short port, sockaddr_in &addr)
{
	memset(&addr, 0, sizeof(addr));  // Zero out address structure
	addr.sin_family = AF_INET;       // Internet address

	hostent *host;  // Resolve name

	if ((host = gethostbyname(address)) == NULL)
	{
		// strerror() will not work for gethostbyname() and hstrerror() 
		// is supposedly obsolete
		printf("error\n");
		throw;// SocketException("Failed to resolve name (gethostbyname())");
	}

	addr.sin_addr.s_addr = *((unsigned long *) host->h_addr_list[0]);

	addr.sin_port = htons(port);     // Assign port in network byte order
}

gal::net::client::client(
		boost::asio::io_service& io_service,
		ip::tcp::resolver::iterator endpoint_iterator):
	gal::net::communicating(io_service),
	io_service_(io_service)
{
	//GALAXY_DEBUG_0_FUNCTION;
	do_connect(endpoint_iterator);
}
void		gal::net::client::do_connect(ip::tcp::resolver::iterator endpoint_iterator) {

	boost::asio::async_connect(socket_, endpoint_iterator,
			[this](boost::system::error_code ec, ip::tcp::resolver::iterator) {
			if (!ec) {
			do_read_header();
			::std::cout << "connected" << ::std::endl;
			}
			});

}





