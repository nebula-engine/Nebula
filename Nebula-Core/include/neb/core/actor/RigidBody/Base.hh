#ifndef __NEBULA_CONTENT_ACTOR_PHYSICS_RIGID_BODY_HPP__
#define __NEBULA_CONTENT_ACTOR_PHYSICS_RIGID_BODY_HPP__

#include <neb/core/actor/Util/Types.hh>
#include <neb/core/actor/RigidActor/Base.hh>

namespace neb { namespace core { namespace actor {
		namespace rigidbody {


			class base:
				virtual public neb::core::actor::rigidactor::base
			{
				public:
					base(sp::shared_ptr<neb::core::actor::util::parent> parent);

					virtual void					init();
					virtual void					release() = 0;
					virtual void					step(gal::std::timestep const & ts);

			};
		}
}}}

#endif








