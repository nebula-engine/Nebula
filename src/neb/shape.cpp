#include <math/free.h>

#include <neb/scene.h>
#include <neb/shape.h>

int			neb::shape::box(math::vec3 s)
{
	neb::shape shape;
	
	shape.type = neb::shape::BOX;
	
	shape.s.x = s.x;
	shape.s.y = s.y;
	shape.s.z = s.z;
	
}
int			neb::shape::box(tinyxml2::XMLElement* element)
{
	type_ = neb::shape::BOX;
	
	s = math::xml_parse_vec3(element->FirstChildElement("s"));
}
int			neb::shape::sphere(float r)
{
	type = neb::shape::SPHERE;
	
	radius = radius;
	s = math::vec3(radius_, radius_, radius_);
	
	geo_ = new physx::PxSphereGeometry(radius_);
}
int			neb::shape::sphere(tinyxml2::XMLElement* element)
{
	type = neb::shape::SPHERE;
	
	radius_ = math::xml_parse_float(element->FirstChildElement("s"));
	s_ = math::vec3(radius_, radius_, radius_);
	
	geo_ = new physx::PxSphereGeometry(radius_);
}
physx::PxGeometry*	neb::shape::to_geometry()
{
	physx::PxGeometry geo = NULL;

	switch(type)
	{
		geo = new physx::PxBoxGeometry(s_.x/2.0, s_.y/2.0, s_.z/2.0);
	}
	
	return geo;
}










