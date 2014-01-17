#ifndef __NEBULA_CONTROL_RIGID_BODY_CONTROL_H__
#define __NEBULA_CONTROL_RIGID_BODY_CONTROL_H__

#include <gal/control/control.h>

#include <neb/actor/Rigid_Actor.h>
#include <neb/config.h>
#include <neb/control/rigid_body/raw.h>

namespace neb {
	namespace control {
		namespace rigid_body {
			class control {
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

				public:
					neb::actor::Base_w		actor_;

					neb::control::rigid_body::raw	raw_;

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








