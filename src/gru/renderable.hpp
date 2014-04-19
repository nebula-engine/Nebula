#ifndef __RENDERABLE_H__
#define __RENDERABLE_H__

#include <memory>

#include <galaxy/flag.hpp>

#include <gru/config.hpp>
#include <gru/gui/layout.hpp>
#include <gru/window/window.hpp>
#include <gru/scene/scene.hpp>

namespace glutpp
{
	class renderable:
		public gal::flag<unsigned int>,
		public std::enable_shared_from_this<renderable>
	{
		public:
			renderable(glutpp::window::window_s window);
			renderable&			operator=(renderable const & r);
			unsigned int			f();
			void				f(unsigned int flag);
			void				init(glutpp::window::window_s window);
			glutpp::window::window_s	get_window();
			void			resize(int w, int h);
			void			render(double time, glutpp::window::window_s window);
		private:
			unsigned int			flag_;


			glutpp::window::window_w		window_;
		public:
			glutpp::scene::scene_s		scene_;
			glutpp::gui::layout_s		layout_;
			glutpp::camera_s		camera_;
	};
}

#endif
