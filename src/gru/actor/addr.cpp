#include <gru/scene/scene.hpp>
#include <gru/actor/actor.hpp>

void glutpp::actor::addr::load_this(glutpp::actor::actor_s actor) {
	assert(actor);

	load_parent(actor);

	int i = actor->i();
	get_vec()->vec_.push_back(i);
}
void glutpp::actor::addr::load_parent(glutpp::actor::actor_s actor0) {
	assert(actor0);
	
	auto parent = actor0->getParent();
	
	auto scene = std::dynamic_pointer_cast<glutpp::scene::scene>(parent);
	auto actor1 = std::dynamic_pointer_cast<glutpp::actor::actor>(parent);

	if(actor1)
	{
		load_this(actor1);
	}
	else
	{
		assert(scene);
		get_scene_addr()->load(scene);
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



