#include <gru/scene/scene.hpp>
#include <gru/scene/addr.hpp>
#include <gru/actor/actor.hpp>
#include <gru/actor/addr.hpp>
#include <gru/actor/parent.hpp>

void		glutpp::actor::addr::load_this(Neb::weak_ptr<glutpp::actor::actor> const & actor) {
	//assert(actor);

	load_parent(actor);
	
	int i = actor->i();

	vec_.push_back(i);
}
void		glutpp::actor::addr::load_parent(Neb::weak_ptr<glutpp::actor::actor> const & actor0) {
	//assert(actor0);
	
	auto parent = actor0->getParent();
	
	auto scene = parent->isScene();//  boost::dynamic_pointer_cast<glutpp::scene::scene>(parent);

	auto actor1 = parent->isActor(); //boost::dynamic_pointer_cast<glutpp::actor::actor>(parent);

	if(actor1) {
		load_this(actor1);
	} else {
		assert(scene);
		scene_.load(scene);
	}
}





