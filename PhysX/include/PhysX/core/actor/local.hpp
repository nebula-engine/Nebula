#ifndef PHYSX_CORE_ACTOR_LOCAL_HPP
#define PHYSX_CORE_ACTOR_LOCAL_HPP

#include <Nebula/Actor/Base.hh>

#include <PhysX/core/actor/util/decl.hpp>

namespace px { namespace core { namespace actor {


	class local:
		virtual public neb::core::actor::local,
		virtual public px::core::actor::base
	{
		public:

			void		hit();
			void		damage();


			virtual sp::shared_ptr<px::core::actor::rigiddynamic::base>		get_projectile();


			float		health_;

	};


}}}

#endif
