#include <Nebula/scene/scene.hpp>
#include <Nebula/scene/addr.hpp>
#include <Nebula/Actor/Base.hpp>
#include <Nebula/Actor/Util/addr.hpp>
#include <Nebula/Actor/Util/parent.hpp>

void		Neb::Actor::addr::load_this(Neb::weak_ptr<Neb::Actor::Base> const & actor) {
	//assert(actor);

	load_parent(actor);
	
	int i = actor->i();

	vec_.push_back(i);
}
void		Neb::Actor::addr::load_parent(Neb::weak_ptr<Neb::Actor::Base> const & actor0) {
	//assert(actor0);
	
	auto parent = actor0->getParent();
	
	auto scene = parent->isScene();//  boost::dynamic_pointer_cast<Neb::scene::scene>(parent);

	auto actor1 = parent->isActor(); //boost::dynamic_pointer_cast<Neb::Actor::actor>(parent);

	if(actor1) {
		load_this(actor1);
	} else {
		assert(scene);
		scene_.load(scene);
	}
}





