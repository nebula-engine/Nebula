#ifndef __NEBULA_CONTENT_ACTOR_PHYSICS_BASE_HPP__
#define __NEBULA_CONTENT_ACTOR_PHYSICS_BASE_HPP__

#include <memory>

#include <GL/glut.h>

//#include <tinyxml/tinyxml.h>

#include <math/transform.h>

#include <PxPhysicsAPI.h>

namespace neb
{
class scene;
	namespace actor
	{
		class Base
		{
			public:
				Base();
				virtual void		init() = 0;
				virtual void		add_force() = 0;
				virtual void		set_pose(math::transform);
				virtual int		fire(int,int,int);

				virtual void		step_remote(double);

				std::weak_ptr<scene>	scene_;
				math::transform		pose_;
				int			i_;
		};
	}
}


#endif








