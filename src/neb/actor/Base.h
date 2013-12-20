#ifndef __NEBULA_CONTENT_ACTOR_PHYSICS_BASE_HPP__
#define __NEBULA_CONTENT_ACTOR_PHYSICS_BASE_HPP__

#include <memory>


//#include <tinyxml/tinyxml.h>

#include <math/transform.h>

#include <glutpp/actor.h>

#include <PxPhysicsAPI.h>

namespace neb
{
	class app;
	class scene;
	namespace actor
	{
		class Base: public glutpp::actor
		{
			public:
				Base();
				virtual void			init() = 0;



				std::shared_ptr<neb::app>	get_app();
				std::shared_ptr<neb::scene>	get_scene();


				virtual void		add_force() = 0;
				virtual void		set_pose(math::transform);
				virtual int		fire();

				virtual void		step_remote(double);



		};
	}
}


#endif








