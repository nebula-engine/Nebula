#include <glutpp/scene/scene.h>
#include <glutpp/actor/actor.h>

void glutpp::actor::addr::load_this(glutpp::actor::actor_s actor) {
	assert(actor);
	
	load_parent(actor);
	
	int i = actor->i();
	get_vec()->vec_.push_back(i);
}
void glutpp::actor::addr::load_parent(glutpp::actor::actor_s actor) {
	assert(actor);
	
	if(!actor->actor_.expired())
	{
		load_this(actor->actor_.lock());
	}
	else
	{
		get_scene_addr()->load(actor->get_scene());
	}
}
glutpp::scene::addr_s glutpp::actor::addr::get_scene_addr() {
	auto p = std::get<1>(tup_);
	assert(p);
	return p;
}
glutpp::actor::vec_int_s glutpp::actor::addr::get_vec() {
	auto p = std::get<0>(tup_);
	assert(p);
	return p;

}



