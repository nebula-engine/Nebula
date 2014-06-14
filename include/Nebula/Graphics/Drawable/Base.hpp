#ifndef NEBULA_GRAPHICS_DRAWABLE_BASE_HPP
#define NEBULA_GRAPHICS_DRAWABLE_BASE_HPP

namespace neb {
	namespace gfx {
		namespace Drawable {
			/** @brief %Drawable
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
					virtual void				draw(sp::shared_ptr<neb::gfx::context::base> context, sp::shared_ptr<neb::glsl::program> p) = 0;


					neb::program_name::e			program_name_;
			};     
		}
	}
}

#endif
