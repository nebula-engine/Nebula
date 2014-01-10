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
	namespace actor
	{
		class Base: public glutpp::actor::actor
		{
			public:
				Base(
						std::shared_ptr<neb::scene::scene>,
						neb::actor::Base_shared = neb::actor::Base_shared());
				virtual ~Base();

				virtual void			init(glutpp::actor::desc_shared);
				virtual void			release();
				
				
				neb::actor::Base_shared		create_actor(
						glutpp::actor::desc_shared);
				neb::actor::Base_shared		create_actor_local(
						glutpp::actor::desc_shared);
				neb::actor::Base_shared		create_actor_remote(
						glutpp::actor::addr_shared,
						glutpp::actor::desc_shared);


				void				create_shapes(glutpp::actor::desc_shared);
				void				create_children(glutpp::actor::desc_shared);

				virtual void				create_physics() {abort();}
				virtual void				init_physics() {abort();}

				std::shared_ptr<neb::app>		get_app();
				std::shared_ptr<neb::scene::scene>	get_scene();

				virtual glutpp::actor::desc_shared	get_desc();
				virtual glutpp::actor::desc_shared	get_projectile();



				virtual void			add_force() {abort();}
				virtual void			set_pose(math::transform);
				virtual int			fire();

				virtual void			step_remote(double);

			public:
				struct
				{
					key_fun_c		key_fun_;
				} conn_;

		};
	}
}


#endif








