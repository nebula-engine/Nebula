#ifndef __NEBULA_CONTENT_ACTOR_PHYSICS_BASE_HPP__
#define __NEBULA_CONTENT_ACTOR_PHYSICS_BASE_HPP__

#include <GL/glut.h>

//#include <tinyxml/tinyxml.h>

#include <PxPhysicsAPI.h>

namespace neb
{
	namespace actor
	{
		class Base
		{
			public:
				Base();
				virtual void Display() = 0;

				physx::PxTransform pose_;

				GLuint list_;
		};
	}
}


#endif








