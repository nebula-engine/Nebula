#ifndef NEBULA_GRAPHICS_DRAWABLE_BASE_HPP
#define NEBULA_GRAPHICS_DRAWABLE_BASE_HPP

#include <neb/util/shared.hpp>

namespace neb {

	namespace glsl {
		class program;
	}

	namespace gfx {

		namespace context {
			class base;
		}

		namespace drawable {
			/** @brief %drawable
			 * 
			 * Contains content to draw in a context (scene, layout, etc.).
			 */
			class base: virtual public neb::std::shared {
				public:
					/** @brief draw
					 *
					 * @param context context in which we are drawing. used by shape to keep track of vertex buffers for various contexts.
					 *
					 * draw into prepared rendering context
					 */
					virtual void				draw(
							sp::shared_ptr<neb::gfx::context::base> context,
							sp::shared_ptr<neb::glsl::program> p) = 0;
			};
			class two: virtual public neb::gfx::drawable::base
			{
			};
			class three: virtual public neb::gfx::drawable::base
			{
			};

		}
	}
}

#endif
