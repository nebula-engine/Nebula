#ifndef __NEB_VIEW_H__
#define __NEB_VIEW_H__

#include <memory>

#include <glutpp/gui/layout.h>
#include <glutpp/window.h>

namespace neb
{
	class view
	{
		public:
			view();
			void				delete_scene();
			void				set_window(glutpp::window*);
			void				Display();
			
			
			neb::scene*		scene_;
			glutpp::gui::layout*	layout_;
			glutpp::window*		window_;
	};
}

#endif
