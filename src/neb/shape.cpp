#include <math/free.h>

#include <neb/scene.h>
#include <neb/shape.h>

neb::box::box(math::vec3 s)
{
	type_ = neb::shape::BOX;
	
	s_ = s;
	
	geo_ = new physx::PxBoxGeometry(s_.x/2.0, s_.y/2.0, s_.z/2.0);
}
neb::box::box(TiXmlElement* element)
{
	type_ = neb::shape::BOX;

	s_ = math::xml_parse_vec3(element->FirstChildElement("s"));
	
	geo_ = new physx::PxBoxGeometry(s_.x/2.0, s_.y/2.0, s_.z/2.0);
}


neb::sphere::sphere(float radius)
{
	type_ = neb::shape::SPHERE;

	radius_ = radius;
	s_ = math::vec3(radius_, radius_, radius_);
	
	geo_ = new physx::PxSphereGeometry(radius_);
}
neb::sphere::sphere(TiXmlElement* element)
{
	type_ = neb::shape::SPHERE;

	radius_ = math::xml_parse_float(element->FirstChildElement("s"));
	s_ = math::vec3(radius_, radius_, radius_);
	
	geo_ = new physx::PxSphereGeometry(radius_);
}





