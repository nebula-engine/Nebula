#include <math/free.h>

#include <neb/physics.h>
#include <neb/scene.h>
#include <neb/simulation_callback.h>
#include <neb/actor/desc.h>

int	neb::actor::desc::load(tinyxml2::XMLElement* element) {

	// xml
	assert(element);
	
	pose.p.from_math(math::xml_parse_vec3(element->FirstChildElement("p"), math::vec3(0,0,0)));
	pose.q.from_math(math::xml_parse_quat(element->FirstChildElement("q")));
	
	
	
	// shapes
	num_shapes_ = 0;
	tinyxml2::XMLElement* element_shape = element->FirstChildElement("shape");
	while(element_shape != NULL)
	{
		shapes_[num_shapes_++].parse_xml(element_shape);
		
		element_shape = element->NextSiblingElement("shape");
	}
	
	// filtering
	filter_data_.simulation_.word0 = neb::filter::type::STATIC;
	filter_data_.simulation_.word1 = neb::filter::RIGID_AGAINST;
	
	filter_data_.scene_query_.word3 = neb::filter::DRIVABLE_SURFACE;
	
	return 0;
}
int	neb::actor::desc::add_shape(glutpp::shape_desc sd) {
	
	int i = num_shapes_++;
	
	shapes_[i] = sd;
	
	return 0;
}



