#ifndef __NEBULA_CONTROL_RIGID_BODY_RAW_H__
#define __NEBULA_CONTROL_RIGID_BODY_RAW_H__

#include <math/quat.hpp>
#include <math/vec3.hpp>

#include <galaxy/network/serial.hpp>

#include <nebula/config.hpp>

namespace neb {
	namespace control {
		namespace rigid_body {
			class raw: public gal::network::serial<raw, gal::network::base> {
				public:
					raw();
					void				load(
							neb::control::rigid_body::control_s);

					type				type_;

					math::quat<float>		q_target_;
					math::vec3<float>		p_target_;

					math::vec3<float>		f_;
					math::vec3<float>		t_;

					math::vec3<float>		force_;
					math::vec3<float>		torque_;
			};
		}
	}
}
#endif

