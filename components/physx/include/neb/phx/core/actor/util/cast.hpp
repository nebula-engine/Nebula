#ifndef PHYSX_CORE_ACTOR_UTIL_CAST_HPP
#define PHYSX_CORE_ACTOR_UTIL_CAST_HPP

#include <neb/core/core/actor/util/cast.hpp>

#include <neb/phx/core/actor/util/decl.hpp>

namespace neb { namespace phx { namespace core { namespace actor { namespace util {

	class cast:
		virtual public neb::core::core::actor::util::cast
	{
		public:
			std::shared_ptr<neb::phx::core::actor::base>				isPxActorBase();
			std::shared_ptr<neb::phx::core::actor::actor::base>			isPxActorActorBase();
			std::shared_ptr<neb::phx::core::actor::rigidactor::base>			isPxActorRigidActorBase();
			std::shared_ptr<neb::phx::core::actor::rigidbody::base>			isPxActorRigidBodyBase();
			std::shared_ptr<neb::phx::core::actor::rigiddynamic::base>		isPxActorRigidDynamicBase();
			std::shared_ptr<neb::phx::core::actor::rigidstatic::base>		isPxActorRigidStaticBase();

	};


}}}}}

#endif



