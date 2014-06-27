#ifndef NEB_FIN_GFX_PHX_CORE_SHAPE_BASE_HPP
#define NEB_FIN_GFX_PHX_CORE_SHAPE_BASE_HPP

#include <neb/phx/core/shape/base.hpp>

#include <neb/gfx/core/shape/base.hpp>

namespace neb { namespace fin { namespace gfx_phx { namespace core { namespace shape {


	class base:
		virtual public neb::gfx::core::shape::base,
		virtual public phx::core::shape::base
	{
		public:
			virtual void						init() = 0;
			virtual void						release() = 0;
			virtual void						step(gal::std::timestep const & ts) = 0;

	};



}}}}}

#endif

