#ifndef NEBULA_GRAPHICS_CONTEXT_BASE_HH
#define NEBULA_GRAPHICS_CONTEXT_BASE_HH

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
			/** @brief Context
			 *
			 * A context with an OpenGL FBO as target.
			 *
			 * @todo allow for manual ordering of context objects in parent's context map
			 * such that things like layouts are render ON TOP of existing scene.'
			 */
			class FBO: public neb::gfx::context::base {
				public:
			};
		}
	}
}
#endif

