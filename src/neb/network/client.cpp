#include <netinet/in.h>
#include <sys/types.h>       // For data types
#include <sys/socket.h>      // For socket(), connect(), send(), and recv()
#include <netdb.h>           // For gethostbyname()
#include <arpa/inet.h>       // For inet_addr()
#include <unistd.h>          // For close()
#include <netinet/in.h>      // For sockaddr_in

#include <neb/network/client.h>

neb::network::client::client(char const * addr, unsigned short port):
		gal::network::communicating(::socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)),
		neb::network::communicating(socket_),
		gal::network::client(addr, port) {
	
	
	
}

