#ifndef NEBULA_GRAPHICS_CONTEXT_BASE_HH
#define NEBULA_GRAPHICS_CONTEXT_BASE_HH

#include <memory>


#include <neb/util/decl.hpp> // gru/config.hpp.in

#include <neb/gfx/util/decl.hpp>
#include <neb/gfx/Viewport.hpp>
#include <neb/gfx/Context/util/Cast.hh>
#include <neb/gfx/GUI/Layout/Base.hh>
#include <neb/gfx/window/Base.hh>
#include <neb/gfx/drawable/base.hpp>


//#include <neb/core/scene/base.hpp>

namespace neb {
	namespace gfx {
		namespace context {
			/** @brief Context
			 *
			 * A rectangle on which to render.
			 * 
			 * - target (window, FBO, etc.)
			 * - viewport
			 * - projection and view camera
			 * - drawable (scene, layout, etc.)
			 * 
			 * @todo allow for manual ordering of context::window objects in window's context map
			 * such that things like layouts are render ON TOP of existing scene.'
			 */
			class base:
				virtual public neb::std::shared,
				virtual public neb::gfx::context::util::cast
			{
				public:
					base();
					base(sp::shared_ptr<neb::gfx::context::util::parent> parent);
					base&						operator=(base const & r);
					void						init();
					void						release();
					virtual void					step(gal::std::timestep const & ts);
					virtual void					render();
					void						resize(int w, int h);

				public:
					/** @brief %Parent
					 * 
					 * @note WEAK
					 */
					sp::shared_ptr<neb::gfx::context::util::parent>		parent_;
				public:
					sp::shared_ptr<neb::gfx::environ::base>			environ_;
			};
		}
	}
}
#endif



