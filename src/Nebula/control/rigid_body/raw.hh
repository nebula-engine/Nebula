#ifndef __NEBULA_CONTROL_RIGID_BODY_RAW_H__
#define __NEBULA_CONTROL_RIGID_BODY_RAW_H__


#include <Nebula/config.hpp>
#include <Nebula/Actor/Util/Types.hh>

namespace Neb {
	namespace Actor {
		namespace Control {
			namespace RigidBody {
				class Raw {
					public:
						Raw();
						void				load(Neb::Actor::Control::RigidBody::Control_w);

						virtual void			serializeDerived(boost::archive::binary_oarchive & ar, unsigned int const & version);
						
						Neb::Actor::Control::RigidBody::Type		type_;
						
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
}
#endif

