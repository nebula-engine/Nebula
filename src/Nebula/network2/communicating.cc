
#include <Nebula/log.hh>
#include <Nebula/config.hh>
#include <Nebula/App/Base.hh>
#include <Nebula/Scene/Base.hh>
#include <Nebula/network/communicating.hh>
#include <Nebula/network/message.hh>
#include <Nebula/Message/Base.hh>

gal::network::communicating::communicating(int socket):
	gal::network::communicating(socket)
{

}
void		gal::network::communicating::process(gal::network::imessage_s buffer) {
	BOOST_LOG_SEV(Neb::lg, debug) << __PRETTY_FUNCTION__;
	
	Neb::WrapperTyped<Neb::Message::IBase>	wrapper;
	
	
	buffer->ar_ >> wrapper;
	
	
	/*
	int type;
	msg->read(type);
	
	switch(type)
	{
		case glutpp::network::type::ACTOR_EVENT:
			printf("DEBUG: actor event message received\n");
			app->recv_actor_event(msg);
			break;
		case glutpp::network::type::CONTROL_UPDATE:
			printf("DEBUG: control update message received\n");
			app->recv_control_update(msg);
			break;
		default:
			printf("DEBUG: unknown message type %i\n", type);
			break;
	}*/

}





