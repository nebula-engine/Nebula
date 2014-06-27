#ifndef NEB_FIN_GFX_PHX_CORE_SHAPE_BOX_HPP
#define NEB_FIN_GFX_PHX_CORE_SHAPE_BOX_HPP

#include <neb/phx/core/shape/box.hpp>

#include <neb/gfx/core/shape/box.hpp>

#include <neb/fin/gfx_phx/core/shape/base.hpp>

namespace neb { namespace fin { namespace gfx_phx { namespace core { namespace shape {

	namespace util {
		class parent;
	}

	class box:
		virtual public neb::gfx::core::shape::box,
		virtual public phx::core::shape::box,
		virtual public neb::fin::gfx_phx::core::shape::base
	{
		public:
			box(::std::shared_ptr<neb::fin::gfx_phx::core::shape::util::parent> parent);

			virtual void						init();
			virtual void						release();
			virtual void						step(gal::std::timestep const & ts);


	};



}}}}}

#endif



