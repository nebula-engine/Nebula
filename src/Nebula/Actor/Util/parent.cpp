#include <Nebula/debug.hpp>
#include <Nebula/Actor/Base.hpp>
#include <Nebula/Actor/Util/parent.hpp>
#include <Nebula/scene/scene.hpp>

Neb::weak_ptr<Neb::Actor::Base>			Neb::Actor::parent::isActor() {
	
	Neb::weak_ptr<Neb::Actor::Base> a = boost::dynamic_pointer_cast<Neb::Actor::Base>(shared_from_this());
	
	return a;
}
Neb::weak_ptr<Neb::Scene::scene>		Neb::Actor::parent::isScene() {
	
	Neb::weak_ptr<Neb::Scene::scene> s = boost::dynamic_pointer_cast<Neb::Scene::scene>(shared_from_this());
	
	return s;
}
Neb::weak_ptr<Neb::Scene::scene>		Neb::Actor::parent::getScene() {
	NEBULA_ACTOR_BASE_FUNC;

	auto scene = isScene(); //boost::dynamic_pointer_cast<Neb::scene::scene>(parent);
	
	if(scene) return scene;
	
	//auto actor = boost::dynamic_pointer_cast<Neb::Actor::actor>(parent);
	auto actor = isActor();
	
	if(actor) return actor->getScene();
	
	abort();
}

