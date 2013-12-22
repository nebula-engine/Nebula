#include <math/free.h>

#include <neb/scene.h>
#include <neb/simulation_callback.h>
#include <neb/actor/desc.h>

int	neb::actor::desc::load(tinyxml2::XMLElement* element) {

	// xml
	assert(element);
	
	pose.p.from_math(math::xml_parse_vec3(element->FirstChildElement("p")));
	pose.q.from_math(math::xml_parse_quat(element->FirstChildElement("q")));
	
	
	
	// choose geometry
	shape = xml_parse_geo(element->FirstChildElement("geo"));
	
	filter_group = neb::simulation_callback::filter_group::NORMAL;
	filter_mask = neb::simulation_callback::filter_group::PROJECTILE;

	return 0;
}



