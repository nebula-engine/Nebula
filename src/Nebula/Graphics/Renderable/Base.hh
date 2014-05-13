#ifndef __RENDERABLE_H__
#define __RENDERABLE_H__

#include <memory>

#include <Nebula/Flag.hh>

#include <Nebula/Types.hh> // gru/config.hpp.in
#include <Nebula/Graphics/Types.hh>

#include <Nebula/Graphics/gui/layout.hh>
#include <Nebula/Graphics/window/window.hh>
#include <Nebula/Scene/scene.hh>

namespace Neb {
	/** @brief Renderable.
	 * @todo eventually replace this with Context and allow multiple Contexts per window and allow scene and layout to have different and overalpping Contexts.
	 */
	class renderable: public std::enable_shared_from_this<renderable> {
		public:
			renderable(Neb::window::window_s window);
			renderable&			operator=(renderable const & r);
			//unsigned int			f();
			//void				f(unsigned int flag);
			void				init(Neb::window::window_s window);

			Neb::window::window_s		getWindow();
			void				resize(int w, int h);
			void				render(double time, Neb::window::window_s window);


			void				moveView(Neb::Camera::View::Base_s &&);
			void				moveScene(Neb::Scene::Base_s &&);
			void				moveLayout(Neb::gui::layout_s &&);

			

		private:
			//unsigned int					flag_;

			Neb::window::window_w				window_;
		private:
			Neb::Scene::Base_s				scene_;
			Neb::gui::layout_s				layout_;
			Neb::Camera::View::Base_s			view_;
			Neb::Camera::Projection::Base_s			proj_;
	};
}

#endif



