#ifndef PHYSX_CORE_ACTOR_BASE
#define PHYSX_CORE_ACTOR_BASE

#include <Nebula/Actor/Base.hh>

#include <PhysX/core/actor/util/cast.hpp>
#include <PhysX/core/actor/util/decl.hpp>

namespace phx { namespace core { namespace actor {

	class base:
		virtual public neb::core::actor::base,
		virtual public phx::core::actor::util::cast
	{
		public:
			base(sp::shared_ptr<neb::core::actor::util::parent> parent);

			
			virtual void		init();
			virtual void		release();
			virtual void		step(neb::core::TimeStep const & ts);


			virtual void		create_physics();
			virtual void		init_physics();



			void			hit();
			void			damage();
			int			fire();


			virtual sp::shared_ptr<phx::core::actor::rigiddynamic::base>		get_projectile();


			float		health_;

	};


}}}

#endif
