
//#include <neb/physics.h>
//#include <neb/scene/scene.h>
//#include <neb/simulation_callback.h>

#include <gru/actor/desc.hpp>
#include <gru/actor/actor.hpp>
#include <gru/shape/desc.hpp>



glutpp::actor::desc::desc() {
}		

glutpp::actor::desc &		glutpp::actor::desc::operator<<(boost::shared_ptr<glutpp::actor::actor> const & actor) {
	GLUTPP_DEBUG_0_FUNCTION;
	
	i_ = actor->i_;
	
	glutpp::master::Global()->actor_raw_factory_->reset(raw_wrapper_.ptr_, actor->raw_->type_);
	
	*(raw_wrapper_.ptr_) = *actor->raw_;
	
	// actor
	boost::shared_ptr<glutpp::actor::desc> ad;
	for(auto it = actor->actors_.begin(); it != actor->actors_.end(); ++it) {
		ad.reset(new glutpp::actor::desc);
		ad->load(it->second);
		actors_.push_back(ad);
	}

	// shape
	boost::shared_ptr<glutpp::shape::desc> sd;
	for(auto it = actor->shapes_.begin(); it != actor->shapes_.end(); ++it) {
		sd.reset(new glutpp::shape::desc);
		sd->operator<<(it->second);
		shapes_.push_back(sd);
	}

	return *this;
}
glutpp::actor::desc& glutpp::actor::desc::operator=(const glutpp::actor::desc& ad) {
	i_ = ad.i_;
	raw_wrapper_.ptr_ = ad.raw_wrapper_.ptr_;
	actors_ = ad.actors_;
	shapes_ = ad.shapes_;
	return *this;
}








