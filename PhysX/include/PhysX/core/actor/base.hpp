#ifndef PHYSX_CORE_ACTOR_BASE
#define PHYSX_CORE_ACTOR_BASE

#include <Nebula/Actor/Base.hh>

#include <PhysX/core/actor/util/cast.hpp>
#include <PhysX/core/actor/util/decl.hpp>
#include <PhysX/core/actor/util/parent.hpp>
#include <PhysX/core/shape/util/parent.hpp>

namespace phx { namespace core { namespace actor {

	class base:
		virtual public neb::core::actor::base,
		virtual public phx::core::actor::util::parent,
		virtual public phx::core::shape::util::parent,
		virtual public phx::core::actor::util::cast
	{
		public:
			base(sp::shared_ptr<phx::core::actor::util::parent> parent);

			
			virtual void		init();
			virtual void		release();
			virtual void		step(neb::core::TimeStep const & ts);


			


			void			hit();
			void			damage(real);
			int			fire();

			
			virtual void		create_physics() = 0;
			virtual void		init_physics() = 0;
			virtual sp::shared_ptr<phx::core::actor::rigiddynamic::local>		get_projectile() = 0;
		
	
			sp::shared_ptr<phx::core::actor::util::parent>				getPxParent();
		public:
			sp::weak_ptr<phx::core::actor::util::parent>				parent_;


			real									health_;

	};


}}}

#endif
