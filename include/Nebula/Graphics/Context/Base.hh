#ifndef NEBULA_GRAPHICS_CONTEXT_BASE_HH
#define NEBULA_GRAPHICS_CONTEXT_BASE_HH

#include <memory>


#include <Nebula/Types.hh> // gru/config.hpp.in

#include <Nebula/Graphics/Types.hh>
#include <Nebula/Graphics/Viewport.hpp>
#include <Nebula/Graphics/Context/Util/Cast.hh>
#include <Nebula/Graphics/GUI/Layout/Base.hh>
#include <Nebula/Graphics/Window/Base.hh>
#include <Nebula/Graphics/Drawable/Base.hpp>


//#include <Nebula/Scene/Base.hh>

namespace neb {
	namespace gfx {
		namespace Context {
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
			class Base:
				virtual public neb::std::shared,
				virtual public neb::gfx::Context::Util::Cast
			{
				public:
					Base();
					Base(sp::shared_ptr<neb::gfx::Context::Util::Parent> parent);
					Base&						operator=(Base const & r);
					void						init();
					void						release();
					virtual void					step(neb::core::TimeStep const & ts);
					virtual void					render();
					void						resize(int w, int h);

				public:
					/** @brief %Parent
					 * 
					 * @note WEAK
					 */
					sp::shared_ptr<neb::gfx::Context::Util::Parent>		parent_;
				public:
					/** @brief %Viewport
					 * 
					 * sub-rectangle within target
					 */
					neb::gfx::Viewport						viewport_;
					/** @brief View Space Camera
					 * 
					 * @note OWNED
					 */
					sp::shared_ptr<neb::gfx::Camera::View::Base>		view_;
					/** @brief Clip Space Camera
					 * 
					 * @note OWNED
					 */
					sp::shared_ptr<neb::gfx::Camera::Projection::Base>		proj_;
					/** @brief %Drawable
					 * 
					 * @note WEAK
					 * 
					 * content to draw
					 */
					 sp::shared_ptr<neb::gfx::Drawable::Base>			drawable_;
			};
		}
	}
}
#endif



