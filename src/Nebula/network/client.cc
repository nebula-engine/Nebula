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

#include <Nebula/network/client.hh>

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

gal::network::client::client(char const * foreign_address, unsigned short foreign_port):
	communicating(::socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)),
	foreign_address_(foreign_address),
	foreign_port_(foreign_port)
{
	//GALAXY_DEBUG_0_FUNCTION;
	
	sockaddr_in destAddr;

	fillAddr(foreign_address_, foreign_port_, destAddr);

	int c = ::connect(socket_, (sockaddr *) &destAddr, sizeof(destAddr));
	if(c < 0)
	{
		printf("connect: %s\n", strerror(errno));
		exit(0);
	}
	
	printf("connected\n");
	
	//start();
	
	//do_connect(endpoint_iterator);
/*	
	gal::asio::message::shared_t msg(new gal::asio::message);
	memcpy(msg->body(), "hello", 5);
	msg->body_length(5);
	msg->encode_header();
	
	write(msg);
*/


}





