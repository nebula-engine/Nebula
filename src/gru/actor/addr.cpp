#include <gru/scene/scene.hpp>
#include <gru/actor/actor.hpp>
#include <gru/actor/addr.hpp>

void		glutpp::actor::addr::load_this(boost::shared_ptr<glutpp::actor::actor> actor) {
	assert(actor);

	load_parent(actor);
	
	int i = actor->i();
	vec_.push_back(i);
}
void		glutpp::actor::addr::load_parent(boost::shared_ptr<glutpp::actor::actor> actor0) {
	assert(actor0);
	
	auto parent = actor0->getParent();
	
	auto scene = boost::dynamic_pointer_cast<glutpp::scene::scene>(parent);
	auto actor1 = boost::dynamic_pointer_cast<glutpp::actor::actor>(parent);

	if(actor1) {
		load_this(actor1);
	} else {
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



