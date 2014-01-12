#ifndef __NEBULA_CONTENT_ACTOR_PHYSICS_RIGID_BODY_CONTROL_H__
#define __NEBULA_CONTENT_ACTOR_PHYSICS_RIGID_BODY_CONTROL_H__

#include <gal/control/control.h>

#include <neb/actor/Rigid_Actor.h>

namespace neb
{
	namespace actor
	{
		namespace rigid_body
		{
			enum control_type {
				NONE = 0,
				T0,
				T1,
			};
			class control
			{
				public:
					control();
			
					virtual int			key_fun(int,int,int,int);
					virtual int			key_fun0(int,int);
					virtual int			key_fun1(int,int);
					
					math::vec3			f();
					math::vec3			t(double);
					math::vec3			t0();
					math::vec3			t1(double);

				private:
					math::quat			q_target_;
					math::vec3			p_target_;

	
					math::vec3			force_;
					math::vec3			torque_;

				public:
					Base_w				actor_;
					
					control_type			type_;

					struct
					{
						key_fun_c		key_fun_;
					} conn_;

					gal::control::control		pid_;
			};
		}
	}
}

#endif








