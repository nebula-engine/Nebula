
//#include <neb/physics.h>
//#include <neb/scene/scene.h>
//#include <neb/simulation_callback.h>

#include <Nebula/Actor/Types.hpp>
#include <Nebula/Actor/Util/desc.hpp>
#include <Nebula/Actor/Base.hpp>
#include <Nebula/shape/desc.hpp>



Neb::Actor::desc::desc(): raw_wrapper_(Neb::master::global()->factories_.actor_raw_) {
}		
Neb::Actor::desc &		Neb::Actor::desc::operator<<(Neb::Actor::Base_w const & actor) {
	GLUTPP_DEBUG_0_FUNCTION;
	
	i_ = actor->i_;
	
	Neb::Actor::raw_u u(Neb::master::global()->factories_.actor_raw_->alloc((short)actor->raw_->type_.val_));
	


	//Neb::master::global()->actor_raw_factory_->reset(raw_wrapper_.ptr_, );
	
	*(raw_wrapper_.ptr_) = *actor->raw_;
	
	// actor
	boost::shared_ptr<Neb::Actor::desc> ad;
	for(auto it = actor->actors_.begin(); it != actor->actors_.end(); ++it) {
		ad.reset(new Neb::Actor::desc);
		ad->load(it->second);
		actors_.push_back(ad);
	}

	// shape
	boost::shared_ptr<Neb::Shape::desc> sd;
	for(auto it = actor->shapes_.begin(); it != actor->shapes_.end(); ++it) {
		sd.reset(new Neb::Shape::desc);
		sd->operator<<(it->second);
		shapes_.push_back(sd);
	}

	return *this;
}
Neb::Actor::desc& Neb::Actor::desc::operator=(const Neb::Actor::desc& ad) {
	i_ = ad.i_;
	*raw_wrapper_.ptr_ = *ad.raw_wrapper_.ptr_;
	actors_ = ad.actors_;
	shapes_ = ad.shapes_;
	return *this;
}








