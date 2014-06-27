#ifndef NEBULA_GRAPHICS_CONTEXT_BASE_HH
#define NEBULA_GRAPHICS_CONTEXT_BASE_HH

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

