#ifndef NEBULA_GRAPHICS_DRAWABLE_BASE_HPP
#define NEBULA_GRAPHICS_DRAWABLE_BASE_HPP

#include <neb/core/itf/shared.hpp>

#include <neb/gfx/camera/util/decl.hpp>
#include <neb/gfx/glsl/util/decl.hpp>

namespace neb {
	namespace gfx {
		namespace context {
			class base;
		}
		
		//typedef neb::gfx::glsl::program::base program;
		class RenderDesc;

		namespace drawable {
			/** @brief %drawable
			 * 
			 * Contains content to draw in a context (scene, layout, etc.).
			 */
			class base: virtual public neb::itf::shared {
				public:
					//virtual void			init() = 0;
					/** @brief draw
					 *
					 * @param context context in which we are drawing. used by shape to keep track of vertex buffers for various contexts.
					 *
					 * draw into prepared rendering context
					 */
					virtual void			draw(RenderDesc const &) = 0;
			};
			class two: virtual public neb::gfx::drawable::base {
				public:
					//virtual void			init() {}
			};
		}
	}
}

#endif
