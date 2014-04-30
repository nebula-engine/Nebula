
#include <gru/actor/actor.hpp>
#include <gru/shape/parent.hpp>


boost::shared_ptr<glutpp::actor::actor> glutpp::shape::parent::isActor() {
	
	boost::shared_ptr<glutpp::actor::actor> a = boost::dynamic_pointer_cast<glutpp::actor::actor>(shared_from_this());
	
	return a;
}
boost::shared_ptr<glutpp::shape::shape> glutpp::shape::parent::isShape() {
	
	boost::shared_ptr<glutpp::shape::shape> s = boost::dynamic_pointer_cast<glutpp::shape::shape>(shared_from_this());
	
	return s;
}


