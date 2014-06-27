#ifndef NEB_FINAL_GFX_PHX_CORE_ACTOR_RIGIDDYNAMIC_BASE_HPP
#define NEB_FINAL_GFX_PHX_CORE_ACTOR_RIGIDDYNAMIC_BASE_HPP

#include <neb/phx/core/actor/rigiddynamic/actor/base.hpp>

#include <neb/final/gfx_phx/core/actor/rigidactor/base.hpp>

namespace neb { namespace fin { namespace gfx_phx { namespace core { namespace actor { namespace rigiddynamic {

	class base:
		virtual public phx::core::actor::rigiddynamic::base,
		virtual public neb::fin::gfx_phx::core::actor::rigidactor::base
	{
		public:
	};
}}}}}}


#endif



