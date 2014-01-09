#include <glutpp/scene/scene.h>
#include <glutpp/actor/actor.h>

void glutpp::actor::addr::load(glutpp::actor::actor_shared actor) {
	assert(actor);
	
	if(!actor_->actor_.expired())
	{
		load(actor_->actor_.lock());
	}
	else
	{
		load(actor_->scene_.lock());
	}
	
	int i = actor->i();
	vec_.vec_.push_back(i);
	
}
void glutpp::actor::addr::load(glutpp::scene::scene_shared scene) {
	assert(scene);
	
	int i = scene->i();
	vec_.vec_.push_back(i);
	
}



void glutpp::actor::addr::write(gal::network::message_shared msg) {
	
		
	
	
	
	
	msg->write(&actor_->i_, sizeof(int));
}
void glutpp::actor::addr::read(gal::network::message_shared msg) {

	vec_.vec_.clear();
	
	int i;
	while(1)
	{
		msg->read(&i, sizeof(int));

		if(i == -1) break;

		vec_.vec_.push_back(i);
	}
	
	
}
size_t glutpp::actor::addr::size() {

}


