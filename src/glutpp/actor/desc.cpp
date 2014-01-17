#include <math/free.h>

//#include <neb/physics.h>
//#include <neb/scene/scene.h>
//#include <neb/simulation_callback.h>
#include <glutpp/actor/desc.h>
#include <glutpp/actor/actor.h>





void glutpp::actor::desc::load(tinyxml2::XMLElement* element) {
	GLUTPP_DEBUG_0_FUNCTION;
	
	get_raw()->load(element);
	
	// shapes
	tinyxml2::XMLElement* element_shape = element->FirstChildElement("shape");

	glutpp::shape::desc_s sd;

	while(element_shape != NULL)
	{
		sd.reset(new glutpp::shape::desc);

		sd->load(element_shape);

		get_shapes()->vec_.push_back(std::make_tuple(sd));

		element_shape = element->NextSiblingElement("shape");
	}

}
void glutpp::actor::desc::load(glutpp::actor::actor_s actor) {
	GLUTPP_DEBUG_0_FUNCTION;

	get_id()->i_ = actor->i_;

	*get_raw() = actor->raw_;

	// shape
	glutpp::shape::desc_s sd;
	for(auto it = actor->shapes_.begin(); it != actor->shapes_.end(); ++it)
	{
		auto shape = it->second;
		
		sd.reset(new glutpp::shape::desc);
		
		sd->load(shape);
		
		get_shapes()->vec_.push_back(std::make_tuple(sd));
	}

	// actor
	glutpp::actor::desc_s ad;
	for(auto it = actor->actors_.begin(); it != actor->actors_.end(); ++it)
	{
		auto a = it->second;
		
		ad.reset(new glutpp::actor::desc);
		
		ad->load(a);
		
		get_actors()->vec_.push_back(std::make_tuple(ad));
	}

}
glutpp::actor::desc& glutpp::actor::desc::operator=(const glutpp::actor::desc& ad) {
	*get_id() = *(ad.get_id());
	*get_raw() = *ad.get_raw();
	*get_actors() = *(ad.get_actors());
	*get_shapes() = *(ad.get_shapes());	
}
glutpp::actor::id_s glutpp::actor::desc::get_id() const {
	auto p = std::get<3>(tup_);
	assert(p);
	return p;
}
glutpp::actor::raw_s glutpp::actor::desc::get_raw() const {
	auto p = std::get<2>(tup_);
	assert(p);
	return p;
}
glutpp::actor::vec_actor_desc_s glutpp::actor::desc::get_actors() const {
	auto p = std::get<1>(tup_);
	assert(p);
	return p;
}
glutpp::actor::vec_shape_desc_s glutpp::actor::desc::get_shapes() const {
	auto p = std::get<0>(tup_);
	assert(p);
	return p;
}








