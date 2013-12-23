#include <neb/app.h>
#include <neb/scene.h>
#include <neb/packet/packet.h>
#include <neb/network/communicating.h>

neb::network::communicating::communicating(int socket): gal::network::communicating(socket) {

}
void	neb::network::communicating::process(gal::network::message::shared_t message) {
	
	assert(!app_.expired());
	
	auto app = app_.lock();
	std::shared_ptr<neb::scene> scene;
	
	neb::packet::packet p;
	
	memcpy(&p, message->body(), message->body_length());
	
	switch(p.type)
	{
		case neb::packet::type::SCENE:
			scene = app->scenes_[p.scene.scene];
			if(scene)
			{
				scene->recv(p);
			}
			break;
	}
}


