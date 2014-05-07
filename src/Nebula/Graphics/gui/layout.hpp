#ifndef __NEBULA_UI_LAYOUT_BASE_HPP__
#define __NEBULA_UI_LAYOUT_BASE_HPP__

#include <map>


#include <PxPhysicsAPI.h>

#include <Nebula/Graphics/gui/object/object.hpp>
#include <Nebula/Graphics/gui/object/object_factory.hpp>
#include <Nebula/Graphics/window/window.hpp>

namespace Neb {
	namespace gui {
		class Desc {
			public:
				template<class Archive> void	serialize(Archive & ar, unsigned int const & version) {
					ar & objects_;
				}
				
				std::vector<Neb::gui::object::Data>		objects_;
		};
		class layout {
			public:
				layout();
				virtual void			init(Neb::renderable_w renderable);
				Neb::window::window_w		get_window();
				
				void				init(Neb::weak_ptr<Neb::gui::Desc>);
				
				
				//void				load_xml(tinyxml2::XMLElement* element);
				//void				create_object(tinyxml2::XMLElement* element);


				void				render(double time);
				void				draw();
				void				connect();




				int				search(int button, int action, int mods);
				int				mouse_button_fun(int button, int action, int mods);
				int				key_fun(int,int,int,int);

				physx::PxMat44				ortho_;

				Neb::Map<Neb::gui::object::object>	objects_;

				Neb::renderable_w			renderable_;
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
