#ifndef NEBULA_ACTOR_RIGID_DYNAMIC_REMOTE_HH
#define NEBULA_ACTOR_RIGID_DYNAMIC_REMOTE_HH

#include <Nebula/Actor/RigidBody/Remote.hh>
#include <Nebula/Actor/RigidDynamic/Base.hh>

namespace neb { namespace core { namespace actor {
namespace neb {
	namespace actor {
		namespace rigiddynamic {
			class Remote:
				virtual public neb::core::actor::rigidbody::Remote,
				virtual public neb::core::actor::rigiddynamic::Base
			{
				public:
					Remote();
					Remote(neb::core::actor::Util::Parent_w);

					virtual void		create_physics();
					virtual void		init_physics();
			};
		}
	}
}

#endif


