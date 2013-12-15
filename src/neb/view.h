#ifndef __NEB_VIEW_H__
#define __NEB_VIEW_H__

#include <memory>

#include <glutpp/gui/layout.h>
#include <glutpp/window.h>

namespace neb
{
	class scene;
	class view
	{
		public:
			view();
			void				delete_scene();
			void				set_window(std::shared_ptr<glutpp::window>);
			void				Display();


			std::shared_ptr<neb::scene>	scene_;

			std::weak_ptr<glutpp::window>	window_;
	};
}

#endif
