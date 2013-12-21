#include <neb/actor/free.h>

int	neb::actor::load_desc(tinyxml2::XMLElement* element, neb::actor::desc * const desc) {
	// xml
	assert(el_actor);
	
	desc->pose_.p = math::xml_parse_vec3( el_actor->FirstChildElement("p"));
	desc->pose_.q = math::xml_parse_quat(el_actor->FirstChildElement("q"));
	
	
	
	// choose geometry
	neb::shape* shape = xml_parse_geo(el_actor->FirstChildElement("geo"));
	assert(shape);

	desc->shape_ = shape;

	desc->filter_group_ = neb::simulation_callback::filter_group::NORMAL;
	desc->filter_mask_  = neb::simulation_callback::filter_group::PROJECTILE;
}

