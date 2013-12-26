#include <math/free.h>

//#include <glutpp/types.h>

#include <neb/scene.h>
#include <neb/shape.h>


physx::PxGeometry*	neb::shape::to_geo()
{
	physx::PxGeometry* geo = NULL;
	
	switch(desc_.type_)
	{
		case glutpp::shape_type::BOX:
			geo = new physx::PxBoxGeometry(desc_.s_.x/2.0, desc_.s_.y/2.0, desc_.s_.z/2.0);
			break;
		case glutpp::shape_type::SPHERE:
			geo = new physx::PxSphereGeometry(desc_.s_.x);
			break;
		default:
			exit(0);
			break;
	}
	
	return geo;
}




