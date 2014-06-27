#ifndef NEB_FINAL_GFX_PHX_CORE_SCENE_BASE_HPP
#define NEB_FINAL_GFX_PHX_CORE_SCENE_BASE_HPP

#include <neb/gfx/core/scene/base.hpp>
#include <neb/phx/core/scene/base.hpp>

namespace neb { namespace fin { namespace gfx_phx { namespace core { namespace scene {

	class base:
		virtual public neb::gfx::core::scene::base,
		virtual public phx::core::scene::base
	{
		public:
			virtual void						init();
			virtual void						release();
			virtual void						step(gal::std::timestep const & ts);

			::std::weak_ptr<neb::core::actor::base>			createActorRigidStaticUninitialized();
			::std::weak_ptr<neb::core::actor::base>			createActorRigidDynamicUninitialized();

	};


}}}}}

#endif


