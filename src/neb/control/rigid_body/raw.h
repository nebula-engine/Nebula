#ifndef __NEBULA_CONTROL_RIGID_BODY_RAW_H__
#define __NEBULA_CONTROL_RIGID_BODY_RAW_H__

#include <math/quat.h>
#include <math/vec3.h>

#include <gal/network/serial.h>

#include <neb/config.h>

namespace neb {
	namespace control {
		namespace rigid_body {
			class raw: public gal::network::serial<raw, gal::network::base> {
				public:
					raw();
					void				load(
							neb::control::rigid_body::control_s);

					type				type_;

					math::quat			q_target_;
					math::vec3			p_target_;

					math::vec3			f_;
					math::vec3			t_;

					math::vec3			force_;
					math::vec3			torque_;
			};
		}
	}
}
#endif

