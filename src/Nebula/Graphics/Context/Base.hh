#ifndef NEBULA_GRAPHICS_CONTEXT_BASE_HH
#define NEBULA_GRAPHICS_CONTEXT_BASE_HH

#include <memory>

#include <Nebula/Flag.hh>

#include <Nebula/Types.hh> // gru/config.hpp.in

#include <Nebula/Graphics/Types.hh>
//#include <Nebula/Graphics/Context/Util/Parent.hh>
#include <Nebula/Graphics/GUI/Layout/Base.hh>
#include <Nebula/Graphics/Window/Base.hh>

#include <Nebula/Scene/Base.hh>

namespace Neb {
	namespace Graphics {
		namespace Context {
			/** @brief Renderable.
			 * @todo eventually replace this with Context and allow multiple Contexts per window and allow scene and layout to have different and overalpping Contexts.
			 */
			class Base: virtual public Neb::Util::Shared {
				public:
					Base();
					Base(Neb::Graphics::Context::Util::Parent_s parent);
					Base&				operator=(Base const & r);
					void				init();

					Neb::Graphics::Context::Util::Parent_s		getParent();

					Neb::Graphics::Context::Base_s			isContextBase();
					
					void				resize(int w, int h);
					void				render(double time, Neb::Graphics::Window::Base_s window);

				private:

					Neb::Graphics::Context::Util::Parent_s		parent_;
				public://private:
					/** @brief scene.
					 * weak because scene is owned by app.
					 */
					Neb::Scene::Base_w				scene_;
					/** @brief layout.
					 * weak because layout is owned by app.
					 */
					Neb::Graphics::GUI::Layout::Base_w			layout_;
					Neb::Graphics::Camera::View::Base_s			view_;
					Neb::Graphics::Camera::Projection::Base_s			proj_;
			};
		}
	}
}
#endif



