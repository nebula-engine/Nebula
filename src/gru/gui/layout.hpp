#ifndef __NEBULA_UI_LAYOUT_BASE_HPP__
#define __NEBULA_UI_LAYOUT_BASE_HPP__

#include <map>

//#include <math/mat44.hpp>

#include <PxPhysicsAPI.h>

#include <gru/gui/object/object.hpp>
#include <gru/gui/object/object_factory.hpp>
#include <gru/window/window.hpp>

namespace glutpp {
	namespace gui {
		class layout {
			public:
				layout();
				virtual void			init(glutpp::renderable_s renderable);
				glutpp::window::window_s	get_window();
				void				load_xml(tinyxml2::XMLElement* element);
				void				create_object(tinyxml2::XMLElement* element);
				void				render(double time);
				void				draw();
				void				connect();
			


	
				int		search(int button, int action, int mods);
				int		mouse_button_fun(int button, int action, int mods);
				int		key_fun(int,int,int,int);

				physx::PxMat44				otrho_;
				
				Neb::Map<glutpp::gui::object::object>	objects_;
				
				glutpp::renderable_w			renderable_;
				// connections
				struct
				{
					boost::signals2::connection		mouse_button_fun_;
					boost::signals2::connection		key_fun_;
				} conns_;


		};
	}
}

#endif
