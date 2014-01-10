#include <assert.h>

#include <netinet/in.h>
#include <sys/types.h>       // For data types
#include <sys/socket.h>      // For socket(), connect(), send(), and recv()
#include <netdb.h>           // For gethostbyname()
#include <arpa/inet.h>       // For inet_addr()
#include <unistd.h>          // For close()
#include <netinet/in.h>      // For sockaddr_in

#include <glutpp/actor/actor.h>

#include <glutpp/scene/desc.h>

#include <glutpp/network/message.h>

#include <neb/config.h>
#include <neb/app.h>
#include <neb/active_transform.h>
#include <neb/network/client.h>
#include <neb/packet/packet.h>
#include <neb/scene/scene.h>

neb::network::client::client(neb::app_shared app, char const * addr, unsigned short port):
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

	// possibly used
	std::shared_ptr<glutpp::network::scene::create>	scene_create;
	std::shared_ptr<glutpp::network::actor::create>	actor_create;
	std::shared_ptr<glutpp::network::actor::create>	actor_update;
	
	// 
	glutpp::scene::desc_shared sd;

	glutpp::actor::addr_shared actor_addr;
	glutpp::actor::desc_shared actor_desc;
	
	int scene_i = -1;
	int window_name = 0;
	
	switch(type)
	{
		case glutpp::network::type::SCENE_CREATE:
			
			scene_create.reset(new glutpp::network::scene::create);
			//scene_desc.reset(new glutpp::scene::desc);
			//vec_actor_desc.reset(new gal::network::vector<glutpp::actor::desc>)
			
			scene_create->read(msg);
			
			
			window_name = 0;
			
			sd = std::get<0>(scene_create->tup_);
			
			
			app->load_scene_remote(sd);
			
			app->activate_scene(window_name, sd->i_);
			
			break;
		case glutpp::network::type::ACTOR_CREATE:

			actor_create.reset(new glutpp::network::actor::create);
			
			actor_create->read(msg);
			
			actor_desc = std::get<0>(actor_create->tup_);
			
			// need seperate create_actor function for remote scene because actor desc already has
			// valid i
			
			app->get_scene(scene_i)->create_actor_remote(actor_addr, actor_desc);
			
			break;
		default:
			printf("unknwon message type %i\n", type);
			abort();
	}
}

