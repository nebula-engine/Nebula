#ifndef __RENDERABLE_H__
#define __RENDERABLE_H__

#include <memory>

#include <gal/flag.h>

#include <glutpp/config.h>
#include <glutpp/gui/layout.h>
#include <glutpp/window/window.h>
#include <glutpp/scene/scene.h>

namespace glutpp
{
	class renderable: public gal::flag, public std::enable_shared_from_this<glutpp::renderable>
	{
		public:
			renderable();
			renderable&			operator=(renderable const &);
			void				init(glutpp::window::window_shared);
			
			void				render(double, glutpp::window::window_shared);
			
			void				resize(int,int);
			
			
			glutpp::window::window_weak	window_;
			
			glutpp::scene::scene_shared		scene_;
			glutpp::gui::layout_shared	layout_;
			glutpp::camera_shared		camera_;
	};
}

#endif
