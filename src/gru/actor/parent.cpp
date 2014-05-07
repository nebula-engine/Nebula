#include <gru/debug.hpp>
#include <gru/actor/actor.hpp>
#include <gru/actor/parent.hpp>
#include <gru/scene/scene.hpp>

Neb::weak_ptr<glutpp::actor::actor>		glutpp::actor::parent::isActor() {
	
	Neb::weak_ptr<glutpp::actor::actor> a = boost::dynamic_pointer_cast<glutpp::actor::actor>(shared_from_this());
	
	return a;
}
Neb::weak_ptr<glutpp::scene::scene>		glutpp::actor::parent::isScene() {
	
	Neb::weak_ptr<glutpp::scene::scene> s = boost::dynamic_pointer_cast<glutpp::scene::scene>(shared_from_this());
	
	return s;
}
Neb::weak_ptr<glutpp::scene::scene>		glutpp::actor::parent::getScene() {
	GRU_ACTOR_ACTOR_FUNC;

	auto scene = isScene(); //boost::dynamic_pointer_cast<glutpp::scene::scene>(parent);
	
	if(scene) return scene;
	
	//auto actor = boost::dynamic_pointer_cast<glutpp::actor::actor>(parent);
	auto actor = isActor();
	
	if(actor) return actor->getScene();
	
	abort();
}

