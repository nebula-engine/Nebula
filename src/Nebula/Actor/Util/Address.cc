#include <Nebula/Scene/Base.hh>
#include <Nebula/Scene/Util/Address.hh>

#include <Nebula/Actor/Base.hh>
#include <Nebula/Actor/Util/Address.hh>
#include <Nebula/Actor/Util/Parent.hh>

void		Neb::Actor::Util::Address::load_this(Neb::Actor::Base_s const & actor) {
	//assert(actor);

	load_parent(actor);
	
	int i = actor->i();

	vec_.push_back(i);
}
void		Neb::Actor::Util::Address::load_parent(Neb::Actor::Base_s const & actor0) {
	//assert(actor0);
	
	auto parent = actor0->getParent();
	
	auto scene = parent->isSceneBase();//  boost::dynamic_pointer_cast<Neb::scene::scene>(parent);

	auto actor1 = parent->isActorBase(); //boost::dynamic_pointer_cast<Neb::Actor::actor>(parent);

	if(actor1) {
		load_this(actor1);
	} else {
		assert(scene);
		scene_.load(scene);
	}
}





