
//#include <neb/physics.h>
//#include <neb/scene/scene.h>
//#include <neb/simulation_callback.h>

#include <neb/fnd/core/actor/util/decl.hpp>
#include <neb/fnd/core/actor/Base.hpp>

//#include <neb/fnd/shape/desc.hh>


/*
neb::fnd::actor::desc::desc(): raw_wrapper_(neb::master::global()->factories_.actor_raw_) {
}		
neb::fnd::actor::desc &		neb::fnd::actor::desc::operator<<(neb::fnd::actor::base_w const & actor) {
	GLUTPP_DEBUG_0_FUNCTION;
	
	i_ = actor->i_;
	
	neb::fnd::actor::raw_u u(neb::master::global()->factories_.actor_raw_->alloc((short)actor->raw_->type_.val_));
	


	//neb::master::global()->actor_raw_factory_->reset(raw_wrapper_.ptr_, );
	
	*(raw_wrapper_.ptr_) = *actor->raw_;
	
	// actor
	boost::shared_ptr<neb::fnd::actor::desc> ad;
	for(auto it = actor->actors_.begin(); it != actor->actors_.end(); ++it) {
		ad.reset(new neb::fnd::actor::desc);
		ad->load(it->second);
		actors_.push_back(ad);
	}

	// shape
	boost::shared_ptr<neb::fnd::shape::desc> sd;
	for(auto it = actor->shapes_.begin(); it != actor->shapes_.end(); ++it) {
		sd.reset(new neb::fnd::shape::desc);
		sd->operator<<(it->second);
		shapes_.push_back(sd);
	}

	return *this;
}
neb::fnd::actor::desc& neb::fnd::actor::desc::operator=(const neb::fnd::actor::desc& ad) {
	i_ = ad.i_;
	*raw_wrapper_.ptr_ = *ad.raw_wrapper_.ptr_;
	actors_ = ad.actors_;
	shapes_ = ad.shapes_;
	return *this;
}
*/







