#include <assert.h>

#include <netinet/in.h>
#include <sys/types.h>       // For data types
#include <sys/socket.h>      // For socket(), connect(), send(), and recv()
#include <netdb.h>           // For gethostbyname()
#include <arpa/inet.h>       // For inet_addr()
#include <unistd.h>          // For close()
#include <netinet/in.h>      // For sockaddr_in

#include <neb/config.h>
#include <neb/network/client.h>
#include <neb/packet/packet.h>

neb::network::client::client(char const * addr, unsigned short port):
	gal::network::communicating(::socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)),
	neb::network::communicating(socket_),
	gal::network::client(addr, port)
{



}
void neb::network::client::process(gal::network::message::shared_t msg) {

	NEBULA_DEBUG_0_FUNCTION;

	assert(!app_.expired());
	assert(msg->body_length() == sizeof(neb::packet::packet));

	neb::packet::packet p;

	memcpy(&p, msg->body(), sizeof(neb::packet::packet));

	switch(p.type)
	{
		case neb::packet::SCENE:
			
			break;
	}
}

