#ifndef NEB_FINAL_GFX_PHX_CORE_ACTOR_BASE_HPP
#define NEB_FINAL_GFX_PHX_CORE_ACTOR_BASE_HPP

#include <neb/gfx/core/actor/base.hpp>
#include <neb/phx/core/actor/base.hpp>

namespace neb { namespace fin { namespace gfx_phx { namespace core { namespace actor {

	class base:
		virtual public phx::core::actor::base,
		virtual public neb::gfx::core::actor::base
	{
		public:
			virtual void						init() = 0;
			virtual void						release() = 0;
			virtual void						step(gal::std::timestep const & ts) = 0;

			//::std::weak_ptr<neb::core::shape::base>			createShapeBoxUninitialized(glm::vec3 size);
			//::std::weak_ptr<neb::core::shape::base>			createShapeBox(glm::vec3 size);
	};
}}}}}


#endif



