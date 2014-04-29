
//#include <math/xml.hpp>


#include <gru/scene/raw.hpp>
#include <gru/scene/scene.hpp>

glutpp::scene::raw::raw():
	flag_(0)
{
	GLUTPP_DEBUG_0_FUNCTION;
	//i_ = -1;
}
/*
void glutpp::scene::raw::load(tinyxml2::XMLElement* element) {
	GLUTPP_DEBUG_0_FUNCTION;
	
	flag_ = math::Xml::parse_int<int>(element->FirstChildElement("flags"), 0);
	
	gravity_ = math::Xml::parse_vec3<double>(element->FirstChildElement("gravity"), math::vec3<double>(0,0,0));
}
*/
void glutpp::scene::raw::load(glutpp::scene::scene_s scene) {
	GLUTPP_DEBUG_0_FUNCTION;

	*this =* scene->raw_;
}


