#ifndef NEBULA_ACTOR_RIGID_DYNAMIC_REMOTE_HH
#define NEBULA_ACTOR_RIGID_DYNAMIC_REMOTE_HH

#include <Nebula/core/actor/RigidBody/Remote.hh>
#include <Nebula/core/actor/RigidDynamic/Base.hh>

namespace neb { namespace core { namespace actor {
namespace neb {
	namespace actor {
		namespace rigiddynamic {
			class remote:
				virtual public neb::core::actor::rigidbody::remote,
				virtual public neb::core::actor::rigiddynamic::base
			{
				public:
					Remote();
					Remote(neb::core::actor::util::parent_w);

					virtual void		create_physics();
					virtual void		init_physics();
			};
		}
	}
}

#endif


