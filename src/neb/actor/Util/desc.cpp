
//#include <neb/physics.h>
//#include <neb/scene/scene.h>
//#include <neb/simulation_callback.h>

#include <neb/core/actor/Util/Types.hh>
#include <neb/core/actor/Base.hh>

//#include <neb/core/shape/desc.hh>


/*
neb::core::actor::desc::desc(): raw_wrapper_(neb::master::global()->factories_.actor_raw_) {
}		
neb::core::actor::desc &		neb::core::actor::desc::operator<<(neb::core::actor::base_w const & actor) {
	GLUTPP_DEBUG_0_FUNCTION;
	
	i_ = actor->i_;
	
	neb::core::actor::raw_u u(neb::master::global()->factories_.actor_raw_->alloc((short)actor->raw_->type_.val_));
	


	//neb::master::global()->actor_raw_factory_->reset(raw_wrapper_.ptr_, );
	
	*(raw_wrapper_.ptr_) = *actor->raw_;
	
	// actor
	boost::shared_ptr<neb::core::actor::desc> ad;
	for(auto it = actor->actors_.begin(); it != actor->actors_.end(); ++it) {
		ad.reset(new neb::core::actor::desc);
		ad->load(it->second);
		actors_.push_back(ad);
	}

	// shape
	boost::shared_ptr<neb::core::shape::desc> sd;
	for(auto it = actor->shapes_.begin(); it != actor->shapes_.end(); ++it) {
		sd.reset(new neb::core::shape::desc);
		sd->operator<<(it->second);
		shapes_.push_back(sd);
	}

	return *this;
}
neb::core::actor::desc& neb::core::actor::desc::operator=(const neb::core::actor::desc& ad) {
	i_ = ad.i_;
	*raw_wrapper_.ptr_ = *ad.raw_wrapper_.ptr_;
	actors_ = ad.actors_;
	shapes_ = ad.shapes_;
	return *this;
}
*/







