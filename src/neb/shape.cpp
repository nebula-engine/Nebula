#include <neb/scene.h>
#include <neb/shape.h>

neb::box::box(TiXmlElement* element)
{
	type_ = neb::shape::BOX;

	s_ = xml_parse_vec3(element->FirstChildElement("s"));
	
	geo_ = new physx::PxBoxGeometry(s_.x/2.0, s_.y/2.0, s_.z/2.0);
}
neb::sphere::sphere(TiXmlElement* element)
{
	type_ = neb::shape::SPHERE;

	radius_ = xml_parse_float(element->FirstChildElement("s"));
	s_ = math::vec3(radius_, radius_, radius_);
	
	geo_ = new physx::PxSphereGeometry(radius_);
}





