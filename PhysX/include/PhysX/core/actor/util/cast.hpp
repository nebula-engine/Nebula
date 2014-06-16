#ifndef PHYSX_CORE_ACTOR_UTIL_CAST_HPP
#define PHYSX_CORE_ACTOR_UTIL_CAST_HPP

#include <Nebula/Actor/Util/Cast.hh>

#include <PhysX/core/actor/util/decl.hpp>

namespace phx { namespace core { namespace actor { namespace util {


	class cast:
		virtual public neb::core::actor::util::cast
	{
		public:
			sp::shared_ptr<phx::core::actor::base>				isPxActorBase();
			sp::shared_ptr<phx::core::actor::rigidactor::base>		isPxActorRigidActorBase();
			sp::shared_ptr<phx::core::actor::rigidbody::base>		isPxActorRigidBodyBase();

	};


}}}}

#endif



