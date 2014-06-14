#ifndef PHYSX_CORE_ACTOR_BASE
#define PHYSX_CORE_ACTOR_BASE

#include <Nebula/Actor/Base.hh>

#include <PhysX/core/actor/util/decl.hpp>

namespace px { namespace core { namespace actor {

	class base: virtual public neb::core::actor::base {
		public:
			base(sp::shared_ptr<neb::core::actor::util::parent> parent);

			void		hit();
			void		damage();
			
			
			virtual sp::shared_ptr<px::core::actor::rigiddynamic::base>		get_projectile();
			

			float		health_;

	};


}}}

#endif
