#ifndef NEBULA_GRAPHICS_CONTEXT_WINDOW_HH
#define NEBULA_GRAPHICS_CONTEXT_WINDOW_HH

#include <memory>


#include <neb/core/util/decl.hpp>

#include <neb/gfx/util/decl.hpp>
#include <neb/gfx/Context/Base.hh>

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
					window();
					virtual void			init(parent_t * const & p);
			};
		}
	}
}
#endif

