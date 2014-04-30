
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
	
	glutpp::master::Global()->actor_raw_factory_->reset(raw_, actor->raw_->type_);
	
	*raw_ = *actor->raw_;
	
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
	*get_id() = *(ad.get_id());
	*get_raw() = *ad.get_raw();
	*get_actors() = *(ad.get_actors());
	*get_shapes() = *(ad.get_shapes());
	return *this;
}
glutpp::actor::id_s glutpp::actor::desc::get_id() const {
	auto p = std::get<0>(tup_);
	assert(p);
	return p;
}
glutpp::actor::raw_s glutpp::actor::desc::get_raw() const {
	auto p = std::get<1>(tup_);
	assert(p);
	return p;
}
glutpp::actor::vec_actor_desc_s glutpp::actor::desc::get_actors() const {
	auto p = std::get<2>(tup_);
	assert(p);
	return p;
}
glutpp::actor::vec_shape_desc_s glutpp::actor::desc::get_shapes() const {
	auto p = std::get<3>(tup_);
	assert(p);
	return p;
}








