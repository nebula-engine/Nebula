#ifndef __NEBULA_CONTENT_ACTOR_PHYSICS_RIGID_BODY_HPP__
#define __NEBULA_CONTENT_ACTOR_PHYSICS_RIGID_BODY_HPP__


#include <neb/actor/Rigid_Actor.h>

namespace neb
{
	namespace actor
	{
		namespace rigid_body {
			class rigid_body: public neb::actor::Rigid_Actor {
				public:
					rigid_body(glutpp::parent_s);
					
					virtual void			init(glutpp::actor::desc_s);
					
					
					
					virtual glutpp::actor::desc_s	get_projectile();
					
				private:
					virtual void			step_local(double);
					virtual void			step_remote(double);

					virtual void			add_force(double);
				public:
					virtual void			print_info();


					virtual void			create_physics() {abort();}
					
					// control
					virtual void			create_control(
							neb::control::rigid_body::raw_s);
				public:
					neb::control::rigid_body::control_s	control_;
				private:
					math::vec3			force_;
					math::vec3			torque_;
			};
		}
	}
}

#endif








