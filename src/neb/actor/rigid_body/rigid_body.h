#ifndef __NEBULA_CONTENT_ACTOR_PHYSICS_RIGID_BODY_HPP__
#define __NEBULA_CONTENT_ACTOR_PHYSICS_RIGID_BODY_HPP__


#include <neb/actor/Rigid_Actor.h>

namespace neb
{
	namespace actor
	{
		namespace rigid_body {
			class rigid_body:
				public neb::actor::Rigid_Actor
			{
				public:
					rigid_body(
							neb::scene::scene_s,
							neb::actor::Base_s = neb::actor::Base_s());

					virtual void			init(glutpp::actor::desc_s);
					virtual void			add_force(double);


					virtual glutpp::actor::desc_s	get_projectile();

					virtual void			step_remote(double);
					
					virtual void			print_info();


					virtual void			create_physics() {abort();}

					control_s			control_;

					math::vec3			force_;
					math::vec3			torque_;
			};
		}
	}
}

#endif








