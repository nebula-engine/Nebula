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
	template<typename SCENE> class renderable:
		public gal::flag<unsigned int>,
		public std::enable_shared_from_this<renderable<SCENE>>
	{
		public:
			typedef glutpp::renderable<SCENE>	RENDERABLE;
			typedef glutpp::gui::layout<RENDERABLE> LAYOUT;
			typedef std::shared_ptr<LAYOUT>		LAYOUT_S;

			renderable(glutpp::window::window_s);
			renderable&			operator=(renderable const &);
			void				init(glutpp::window::window_s);
			glutpp::window::window_s	get_window();
			
			void				render(double, glutpp::window::window_s);
			
			void				resize(int,int);
			
		private:
			unsigned int			f();
			void				f(unsigned int);
			unsigned int			flag_;
		
		
			glutpp::window::window_w	window_;
		public:
			std::shared_ptr<SCENE>		scene_;
			LAYOUT_S			layout_;
			glutpp::camera_s		camera_;
	};
}

#endif
