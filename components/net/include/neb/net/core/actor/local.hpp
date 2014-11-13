#ifndef PHYSX_CORE_ACTOR_LOCAL_HPP
#define PHYSX_CORE_ACTOR_LOCAL_HPP

#include <neb/core/actor/Local.hh>

#include <PhysX/core/actor/base.hpp>
#include <PhysX/core/actor/util/decl.hpp>

namespace phx { namespace core { namespace actor {


	class local:
		virtual public neb::core::actor::local,
		virtual public phx::core::actor::base
	{
		public:
			local(std::shared_ptr<phx::core::actor::util::parent> parent);

			virtual void		init();
			virtual void		release() = 0;
			virtual void		step(gal::etc::timestep const & ts);



			void		hit();
			void		damage();





	};


}}}

#endif
