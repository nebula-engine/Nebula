
#include <gru/actor/actor.hpp>
#include <gru/actor/parent.hpp>
#include <gru/scene/scene.hpp>

boost::shared_ptr<glutpp::actor::actor> glutpp::actor::parent::isActor() {
	
	boost::shared_ptr<glutpp::actor::actor> a = boost::dynamic_pointer_cast<glutpp::actor::actor>(shared_from_this());
	
	return a;
}
boost::shared_ptr<glutpp::scene::scene> glutpp::actor::parent::isScene() {
	
	boost::shared_ptr<glutpp::scene::scene> s = boost::dynamic_pointer_cast<glutpp::scene::scene>(shared_from_this());
	
	return s;
}


