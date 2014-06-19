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
			sp::shared_ptr<phx::core::actor::actor::base>			isPxActorActorBase();
			sp::shared_ptr<phx::core::actor::rigidactor::base>		isPxActorRigidActorBase();
			sp::shared_ptr<phx::core::actor::rigidbody::base>		isPxActorRigidBodyBase();
			sp::shared_ptr<phx::core::actor::rigiddynamic::base>		isPxActorRigidDynamicBase();
			sp::shared_ptr<phx::core::actor::rigidstatic::base>		isPxActorRigidStaticBase();

	};


}}}}

#endif



