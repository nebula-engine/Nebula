#ifndef NEB_FINAL_GFX_PHX_CORE_ACTOR_RIGIDSTATIC_BASE_HPP
#define NEB_FINAL_GFX_PHX_CORE_ACTOR_RIGIDSTATIC_BASE_HPP

#include <neb/phx/core/actor/rigidstatic/base.hpp>

#include <neb/fin/gfx_phx/core/actor/rigidactor/base.hpp>

namespace neb { namespace fin { namespace gfx_phx { namespace core { namespace actor { namespace rigidstatic {

	class base:
		virtual public phx::core::actor::rigidstatic::base,
		virtual public neb::fin::gfx_phx::core::actor::rigidactor::base
	{
		public:
			base(std::shared_ptr<neb::fin::gfx_phx::core::actor::util::parent> parent);
			~base();
			virtual void						init();
			virtual void						release();
			virtual void						step(gal::etc::timestep const & ts);

	};


}}}}}}


#endif



