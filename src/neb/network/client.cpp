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

#include <glutpp/network/scene_create.h>
#include <glutpp/network/actor_create.h>

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
	std::shared_ptr<glutpp::network::scene_create>			scene_create;
	std::shared_ptr<glutpp::scene::desc>				scene_desc;
	std::shared_ptr<gal::network::vector<glutpp::actor::desc>>	vec_actor_desc;
	
	
	std::shared_ptr<glutpp::network::actor_create>	actor_create;
	std::shared_ptr<glutpp::actor::addr>		actor_addr;
	std::shared_ptr<glutpp::actor::raw>		actor_raw;
	
	
	int scene_i = -1;
	glutpp::actor::desc_shared ad;
	int window_name = 0;
	
	switch(type)
	{
		case glutpp::network::type::SCENE:
			
			scene_create.reset(new glutpp::network::scene_create(type));
			scene_desc.reset(new glutpp::scene::desc);
			vec_actor_desc.reset(new gal::network::vector<glutpp::actor::desc>);
			
			
			scene_create->read_expand(vec_actor_desc, scene_desc);
			
			
			window_name = 0;
			
			app->load_scene_remote(scene_desc);
			
			
			app->activate_scene(window_name, scene_desc->i_);
			
			break;
		case glutpp::network::type::ACTOR_CREATE:
			actor_create.reset(new glutpp::network::actor_create(type));
			actor_addr.reset(new glutpp::actor::addr);
			actor_raw.reset(new glutpp::actor::raw);
			
			
			
			// need seperate create_actor function for remote scene because actor desc already has
			// valid i
			app->get_scene(scene_i)->create_actor_remote(actor_addr, actor_raw);

			break;
		default:
			printf("unknwon message type %i\n", type);
			abort();
	}
}

