#ifndef NEBULA_GRAPHICS_CONTEXT_WINDOW_HH
#define NEBULA_GRAPHICS_CONTEXT_WINDOW_HH

#include <memory>


#include <Nebula/Types.hh> // gru/config.hpp.in

#include <Nebula/Graphics/Types.hh>
#include <Nebula/Graphics/Context/Util/Cast.hh>
#include <Nebula/Graphics/GUI/Layout/Base.hh>
#include <Nebula/Graphics/Window/Base.hh>

#include <Nebula/Scene/Base.hh>

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
			class Window:
				virtual public neb::gfx::context::base
			{
				public:
					Window(sp::shared_ptr<neb::gfx::window::base> window);
					virtual void					init();
				public:
					sp::shared_ptr<neb::gfx::window::base>	window_;
			};
		}
	}
}
#endif

