#ifndef NEBULA_GRAPHICS_CONTEXT_FBO_MULTI_HPP
#define NEBULA_GRAPHICS_CONTEXT_FBO_MULTI_HPP

#include <memory>

#include <neb/gfx/util/decl.hpp>
#include <neb/gfx/Context/Window.hpp>

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
			class fbo_multi:
				public neb::gfx::context::window
			{
				public:
					fbo_multi();
					virtual void				init(parent_t * const & p);
					virtual void				render();
					
					GLuint					framebuffer_;

					std::weak_ptr<neb::gfx::texture>	texture_;
					GLint*					layer_;
					GLuint					layer_count_;
			};
		}
	}
}
#endif

