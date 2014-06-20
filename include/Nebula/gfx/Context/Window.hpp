#ifndef NEBULA_GRAPHICS_CONTEXT_WINDOW_HH
#define NEBULA_GRAPHICS_CONTEXT_WINDOW_HH

#include <memory>


#include <Nebula/util/decl.hpp> // gru/config.hpp.in

#include <Nebula/gfx/util/decl.hpp>
#include <Nebula/gfx/Context/Util/Cast.hh>
#include <Nebula/gfx/GUI/Layout/Base.hh>
#include <Nebula/gfx/window/Base.hh>

#include <Nebula/core/scene/Base.hh>

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

