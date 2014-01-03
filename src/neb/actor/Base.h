#ifndef __NEBULA_CONTENT_ACTOR_PHYSICS_BASE_HPP__
#define __NEBULA_CONTENT_ACTOR_PHYSICS_BASE_HPP__

#include <memory>


//#include <tinyxml/tinyxml.h>

#include <math/transform.h>

#include <glutpp/actor/actor.h>

#include <PxPhysicsAPI.h>

#include <glutpp/actor/desc.h>

#include <neb/config.h>

namespace neb
{
	class app;
	namespace scene
	{
		class scene;
	}
	namespace actor
	{
		class Base: public glutpp::actor::actor
		{
			public:
				Base(
					glutpp::actor::desc*,
					std::shared_ptr<neb::scene::scene>,
					neb::actor::Base_shared = neb::actor::Base_shared());
				
				virtual void			init();
				virtual void			release();
				
				void				create_actor(glutpp::actor::desc*);
				void				create_shapes();
				void				create_children();
				
				virtual void			create_physics() {abort();}
				virtual void			init_physics() {abort();}

				std::shared_ptr<neb::app>		get_app();
				std::shared_ptr<neb::scene::scene>	get_scene();

				virtual glutpp::actor::desc*		get_desc();
				virtual glutpp::actor::desc*		get_projectile();
				
				
				
				virtual void			add_force() {abort();}
				virtual void			set_pose(math::transform);
				virtual int			fire();
				
				virtual void			step_remote(double);
				

		};
	}
}


#endif








