#ifndef NEBULA_GRAPHICS_CONTEXT_WINDOW_HH
#define NEBULA_GRAPHICS_CONTEXT_WINDOW_HH

#include <memory>


#include <neb/util/decl.hpp> // gru/config.hpp.in

#include <neb/gfx/util/decl.hpp>
#include <neb/gfx/Context/Util/Cast.hh>
#include <neb/gfx/GUI/Layout/Base.hh>
#include <neb/gfx/window/Base.hh>

#include <neb/core/scene/base.hpp>

namespace neb {
	namespace gfx {
		namespace context {
			/** @brief %Context
			 *
			 * A context with a window as the target.
			 *
			 * @todo allow for manual ordering of context::window objects in window's context map
			 * such that things like layouts are render ON TOP of existing scene.'
			 */
			class window:
				virtual public neb::gfx::context::base
			{
				public:
					window(sp::shared_ptr<neb::gfx::window::base> window);
					virtual void					init();
				public:
					sp::shared_ptr<neb::gfx::window::base>	window_;
			};
		}
	}
}
#endif

