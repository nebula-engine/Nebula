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
			local(sp::shared_ptr<phx::core::actor::util::parent> parent);

			virtual void		init();
			virtual void		release();
			virtual void		step(neb::core::TimeStep const & ts);



			void		hit();
			void		damage();




			float		health_;

	};


}}}

#endif
