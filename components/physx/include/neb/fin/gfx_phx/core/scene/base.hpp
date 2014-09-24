#ifndef NEB_FINAL_GFX_PHX_CORE_SCENE_BASE_HPP
#define NEB_FINAL_GFX_PHX_CORE_SCENE_BASE_HPP

#include <neb/gfx/core/scene/base.hpp>

#include <neb/phx/core/scene/base.hpp>

#include <neb/fin/gfx_phx/core/actor/util/decl.hpp>
#include <neb/fin/gfx_phx/core/scene/util/parent.hpp>
#include <neb/fin/gfx_phx/core/actor/util/parent.hpp>

typedef weak_ptr<neb::core::core::actor::base> wbase;

namespace neb { namespace fin { namespace gfx_phx { namespace core { namespace scene {
	class base:
		virtual public neb::gfx::core::scene::base,
		virtual public phx::core::scene::base,
		virtual public neb::fin::gfx_phx::core::actor::util::parent
	{
		public:
			base(std::shared_ptr<neb::fin::gfx_phx::core::scene::util::parent> parent);
			virtual void			init();
			virtual void			release();
			virtual void			step(gal::etc::timestep const & ts);
			virtual wbase			createActorBase(neb::core::pose);
			virtual wbase			createActorRigidStaticUninitialized();
			virtual wbase			createActorRigidDynamicUninitialized();
	};
}}}}}

#endif

