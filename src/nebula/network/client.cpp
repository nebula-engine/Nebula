#include <assert.h>

#include <netinet/in.h>
#include <sys/types.h>       // For data types
#include <sys/socket.h>      // For socket(), connect(), send(), and recv()
#include <netdb.h>           // For gethostbyname()
#include <arpa/inet.h>       // For inet_addr()
#include <unistd.h>          // For close()
#include <netinet/in.h>      // For sockaddr_in

#include <math/free.hpp>

#include <gru/actor/actor.hpp>
#include <gru/scene/desc.hpp>
#include <gru/network/message.hpp>

#include <nebula/config.hpp>
#include <nebula/app.hpp>
#include <nebula/network/client.hpp>
#include <nebula/network/message.hpp>
#include <nebula/scene/scene.hpp>

neb::network::client::client(neb::app_s app, char const * addr, unsigned short port):
	gal::network::communicating(::socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)),
	neb::network::communicating(app, socket_),
	gal::network::client(addr, port)
{

}
void neb::network::client::process(gal::network::message::shared_t msg) {
	NEBULA_DEBUG_1_FUNCTION;

	assert(!app_.expired());
	auto app = app_.lock();
	//assert(msg->body_length() == sizeof(neb::packet::packet));

	//neb::packet::packet p;
	//memcpy(&p, msg->body(), sizeof(neb::packet::packet));

	//size_t len = msg->body_length();
	
	int type;
	msg->read(&type, sizeof(int));
	
	math::hexdump(&type, sizeof(int));
	
	// possibly used
	std::shared_ptr<glutpp::network::scene::create>			scene_create;
	std::shared_ptr<glutpp::network::actor::create>			actor_create;
	std::shared_ptr<glutpp::network::actor::update>			actor_update;
	std::shared_ptr<neb::network::control::rigid_body::create>	control_create;
	
	//
	
	glutpp::window::window_s window;
	
	neb::actor::Base_s			actor;
	neb::actor::rigid_body::rigid_body_s	rigidbody;
	
	glutpp::scene::desc_s sd;
	
	
	glutpp::scene::addr_s scene_addr;
	
	glutpp::actor::addr_s actor_addr;
	glutpp::actor::desc_s actor_desc;
	
	neb::control::rigid_body::raw_s	control_raw;
	
	glutpp::network::actor::vec_addr_raw_s vec;

	int window_name = 0;
	
	switch(type)
	{
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
				glutpp::actor::addr_s addr = std::get<1>(t);
				glutpp::actor::raw_s raw = std::get<0>(t);
				
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
			rigidbody = actor->to_rigid_body();
			
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
}

