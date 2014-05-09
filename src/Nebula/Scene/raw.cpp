
//#include <math/xml.hpp>


#include <Nebula/scene/raw.hpp>
#include <Nebula/scene/scene.hpp>

Neb::Scene::raw::raw():
	flag_(0)
{
	GLUTPP_DEBUG_0_FUNCTION;
	//i_ = -1;
}
/*
void Neb::scene::raw::load(tinyxml2::XMLElement* element) {
	GLUTPP_DEBUG_0_FUNCTION;
	
	flag_ = math::Xml::parse_int<int>(element->FirstChildElement("flags"), 0);
	
	gravity_ = math::Xml::parse_vec3<double>(element->FirstChildElement("gravity"), math::vec3<double>(0,0,0));
}
*/
void Neb::Scene::raw::load(Neb::Scene::scene_w scene) {
	GLUTPP_DEBUG_0_FUNCTION;

	auto s = scene.lock();
	assert(s);
	*this = *s->raw_;
}


