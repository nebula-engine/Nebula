#include <gru/actor/actor.hpp>
#include <gru/actor/parent.hpp>


glutpp::actor::actor_s glutpp::actor::parent::isActor() {
	
	glutpp::actor::actor_s a = std::dynamic_pointer_cast<glutpp::actor::actor>(shared_from_this());
	
	return a;
}
glutpp::shape::shape_s glutpp::actor::parent::isShape() {
	
	glutpp::shape::shape_s s = std::dynamic_pointer_cast<glutpp::shape::shape>(shared_from_this());
	
	return s;
}


