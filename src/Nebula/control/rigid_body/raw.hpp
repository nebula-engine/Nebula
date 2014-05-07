#ifndef __NEBULA_CONTROL_RIGID_BODY_RAW_H__
#define __NEBULA_CONTROL_RIGID_BODY_RAW_H__


#include <nebula/config.hpp>

namespace neb {
	namespace control {
		namespace rigid_body {
			class raw {
				public:
					raw();
					void				load(neb::control::rigid_body::control_s);

					virtual void			serializeDerived(boost::archive::binary_oarchive & ar, unsigned int const & version);

					type				type_;

					physx::PxQuat			q_target_;
					physx::PxVec3			p_target_;

					physx::PxVec3			f_;
					physx::PxVec3			t_;

					physx::PxVec3			force_;
					physx::PxVec3			torque_;
			};
		}
	}
}
#endif

