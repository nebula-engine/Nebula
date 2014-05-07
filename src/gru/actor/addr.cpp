#include <gru/scene/scene.hpp>
#include <gru/actor/actor.hpp>
#include <gru/actor/addr.hpp>

void		glutpp::actor::addr::load_this(Neb::unique_ptr<glutpp::actor::actor> const & actor) {
	//assert(actor);

	load_parent(actor);
	
	int i = actor->i();

	vec_.push_back(i);
}
void		glutpp::actor::addr::load_parent(Neb::unique_ptr<glutpp::actor::actor> const & actor0) {
	//assert(actor0);
	
	auto parent = actor0->getParent();
	
	auto scene = boost::dynamic_pointer_cast<glutpp::scene::scene>(parent);

	auto actor1 = boost::dynamic_pointer_cast<glutpp::actor::actor>(parent);

	if(actor1) {
		load_this(actor1);
	} else {
		assert(scene);
		scene_.load(scene);
	}
}





