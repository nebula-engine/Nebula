#include <assert.h>

#include <netinet/in.h>
#include <sys/types.h>       // For data types
#include <sys/socket.h>      // For socket(), connect(), send(), and recv()
#include <netdb.h>           // For gethostbyname()
#include <arpa/inet.h>       // For inet_addr()
#include <unistd.h>          // For close()
#include <netinet/in.h>      // For sockaddr_in

#include <glutpp/scene/desc.h>

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

	char* data = msg->body();
	char* head = data;
	//size_t len = msg->body_length();

	int type;
	memcpy(&type, head, sizeof(int));
	head += sizeof(int);

	// possiblly used
	int scene_i = -1;
	glutpp::scene::desc_shared sd;
	glutpp::actor::desc_shared ad;
	neb::active_transform::set* ats = NULL;
	int window_name = 0;

	switch(type)
	{
		case glutpp::network::type::SCENE:

			sd.reset(new glutpp::scene::desc);
			sd->read(head);
			
			window_name = 0;

			app->load_scene_remote(sd);
			
			app->activate_scene(window_name, sd->raw_.i_);

			break;
		case glutpp::network::type::ACTIVE_TRANSFORM_SET:
			
			ats = new neb::active_transform::set;
			ats->read(head);
			
			app->get_scene(ats->raw_.name_scene_)->read(ats);
			
			break;
		case glutpp::network::type::ACTOR_CREATE:
			
			// scene_i
			memcpy(&scene_i, head, sizeof(int));
			head += sizeof(int);
			
			// actor desc
			ad.reset(new glutpp::actor::desc);
			ad->read(head);
			
			// need seperate create_actor function for remote scene because actor desc already has
			// valid i
			app->get_scene(scene_i)->create_actor(ad);
			
			break;
		default:
			printf("unknwon message type %i\n", type);
			abort();
	}
}

