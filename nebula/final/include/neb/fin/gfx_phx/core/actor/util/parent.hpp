#ifndef NEB_FIN_GFX_PHX_CORE_ACTOR_UTIL_PARENT_HPP
#define NEB_FIN_GFX_PHX_CORE_ACTOR_UTIL_PARENT_HPP

#include <neb/gfx/core/actor/util/parent.hpp>
#include <neb/phx/core/actor/util/parent.hpp>


namespace neb { namespace fin { namespace gfx_phx { namespace core { namespace actor { namespace util {


	class parent:
		virtual public neb::gfx::core::actor::util::parent,
		virtual public neb::phx::core::actor::util::parent
	{
		public:

	};



}}}}}}

#endif


