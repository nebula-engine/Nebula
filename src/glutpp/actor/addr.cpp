#include <glutpp/scene/scene.h>
#include <glutpp/actor/actor.h>

void glutpp::actor::addr::load(glutpp::actor::actor_shared actor) {
	assert(actor);
	
	
	if(!actor->actor_.expired())
	{
		load(actor->actor_.lock());
	}
	else
	{
		scene_addr_.load(actor->get_scene());
	}
	
	int i = actor->i();
	vec_.vec_.push_back(i);
	
}



void glutpp::actor::addr::write(gal::network::message_shared msg) {
	
	vec_.write(msg);
}
void glutpp::actor::addr::read(gal::network::message_shared msg) {

	vec_.read(msg);
}
size_t glutpp::actor::addr::size() {

}


