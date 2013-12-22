#include <math/free.h>

#include <neb/scene.h>
#include <neb/shape.h>

int			neb::shape::box(math::vec3 ns)
{
	type = neb::shape::BOX;
	
	s.from_math(ns);
	
	return 0;
}
int			neb::shape::box(tinyxml2::XMLElement* element)
{
	type = neb::shape::BOX;
	
	s.from_math(math::xml_parse_vec3(element->FirstChildElement("s")));

	return 0;
}
int			neb::shape::sphere(float r)
{
	type = neb::shape::SPHERE;
	
	s.from_math(math::vec3(r, r, r));

	return 0;
}
int			neb::shape::sphere(tinyxml2::XMLElement* element)
{
	type = neb::shape::SPHERE;
	
	float r = math::xml_parse_float(element->FirstChildElement("s"));
	s.from_math(math::vec3(r, r, r));

	return 0;
}
physx::PxGeometry*	neb::shape::to_geo()
{
	physx::PxGeometry* geo = NULL;

	switch(type)
	{
		case neb::shape::BOX:
			geo = new physx::PxBoxGeometry(s.x/2.0, s.y/2.0, s.z/2.0);
			break;
		case neb::shape::SPHERE:
			geo = new physx::PxSphereGeometry(s.x);
			break;
	}
	
	return geo;
}










