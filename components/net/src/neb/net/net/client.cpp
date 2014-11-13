#include <assert.h>

/*#include <netinet/in.h>
#include <sys/types.h>       // For data types
#include <sys/socket.h>      // For socket(), connect(), send(), and recv()
#include <netdb.h>           // For gethostbyname()
#include <arpa/inet.h>       // For inet_addr()
#include <unistd.h>          // For close()
#include <netinet/in.h>      // For sockaddr_in
*/
//#include <math/free.hpp>

#include <gal/net/message.hpp>

#include <neb/core/actor/base.hpp>

#include <neb/config.hh>
#include <neb/app/Base.hh>
#include <neb/core/scene/Base.hh>

neb::Network::Client::Client(boost::asio::io_service& io_service, ip::tcp::resolver::iterator endpoint_iterator):
	gal::net::communicating(io_service),
	neb::Network::Communicating(io_service),
	gal::net::client(io_service, endpoint_iterator)
{

}
void		neb::Network::Client::process(std::shared_ptr<gal::net::imessage> message) {

	//assert(msg->body_length() == sizeof(neb::packet::packet));

	//neb::packet::packet p;
	//memcpy(&p, msg->body(), sizeof(neb::packet::packet));

	//size_t len = msg->body_length();
	/*
	int type;
	msg->read(&type, sizeof(int));
	
	math::hexdump(&type, sizeof(int));
	
	// possibly used
	std::shared_ptr<glutpp::network::scene::create>			scene_create;
	std::shared_ptr<glutpp::network::actor::create>			actor_create;
	std::shared_ptr<glutpp::network::actor::update>			actor_update;
	std::shared_ptr<neb::network::control::rigid_body::create>	control_create;
	
	//
	
	std::shared_ptr<glutpp::window::window> window;
	
	std::shared_ptr<neb::core::actor::base>			actor;
	std::shared_ptr<neb::core::actor::rigidbody::RigidBody>	rigidbody;
	
	std::shared_ptr<glutpp::scene::desc> sd;
	
	
	std::shared_ptr<glutpp::scene::addr> scene_addr;
	
	std::shared_ptr<glutpp::actor::addr> actor_addr;
	std::shared_ptr<glutpp::actor::desc> actor_desc;
	
	std::shared_ptr<neb::control::rigid_body::raw>	control_raw;
	
	std::shared_ptr<glutpp::network::actor::vec_addr_raw> vec;

	int window_name = 0;
	
	switch(type) {
		case glutpp::network::type::SCENE_CREATE:
			printf("DEBUG: message SCENE_CREATE received\n");
			
			scene_create.reset(new glutpp::network::scene::create);
			//scene_desc.reset(new glutpp::scene::desc);
			//vec_actor_desc.reset(new gal::network::vector<glutpp::actor::desc>)
			
			scene_create->read(msg);
			
			
			window_name = 0;
			
			sd = std::get<0>(scene_create->tup_);
			
			
			app->load_scene_remote(sd);
			
			app->activate_scene(window_name, sd->get_id()->i_);
			
			break;
		case glutpp::network::type::ACTOR_CREATE:
			printf("DEBUG: message ACTOR_CREATE received\n");

			actor_create.reset(new glutpp::network::actor::create);
			
			actor_create->read(msg);
			
			actor_desc = actor_create->get_desc();
			actor_addr = actor_create->get_addr();
			
			scene_addr = actor_addr->get_scene_addr();
			
			app->get_scene(scene_addr)->create_actor_remote(
					actor_addr,
					actor_desc);
			
			break;
		case glutpp::network::type::ACTOR_UPDATE:
			printf("DEBUG: message ACTOR_UPDATE received\n");

			actor_update.reset(new glutpp::network::actor::update);

			actor_update->read(msg);
			
			vec = std::get<0>(actor_update->tup_);
			
			for(auto it = vec->vec_.begin(); it != vec->vec_.end(); ++it)
			{
				auto t = *it;
				std::shared_ptr<glutpp::actor::addr> addr = std::get<1>(t);
				std::shared_ptr<glutpp::actor::raw> raw = std::get<0>(t);
				
				auto a = app->get_actor(addr);
				if(a)
				{
					a->get_raw()->operator=(*raw);
				}
				else
				{
					printf("WARNING: actor not found\n");
				}
			}
			
			break;
		case glutpp::network::type::CONTROL_CREATE:
			printf("DEBUG: message CONTROL_CREATE received\n");
			
			control_create.reset(new neb::network::control::rigid_body::create);
			
			control_create->read(msg);
			
			actor_addr = control_create->get_addr();
			
			window = app->get_window(0);
			
			actor = app->get_actor(actor_addr);
			rigidbody = actor->isRigidBody();
			
			if(window && rigidbody)
			{
				rigidbody->connect(window);
				
				rigidbody->create_control(control_raw);
			}
			
			break;
		default:
			printf("unknwon message type %i\n", type);
			//abort();
	}
*/
}




