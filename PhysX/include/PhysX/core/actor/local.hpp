#ifndef PHYSX_CORE_ACTOR_LOCAL_HPP
#define PHYSX_CORE_ACTOR_LOCAL_HPP

#include <Nebula/Actor/Local.hh>

#include <PhysX/core/actor/base.hpp>
#include <PhysX/core/actor/util/decl.hpp>

namespace phx { namespace core { namespace actor {


	class local:
		virtual public neb::core::actor::local,
		virtual public phx::core::actor::base
	{
		public:
			local(sp::shared_ptr<neb::core::actor::util::parent> parent);

			void		hit();
			void		damage();


			virtual sp::shared_ptr<phx::core::actor::rigiddynamic::base>		get_projectile();


			float		health_;

	};


}}}

#endif
