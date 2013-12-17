#ifndef __NEBULA_UI_LAYOUT_BASE_HPP__
#define __NEBULA_UI_LAYOUT_BASE_HPP__

#include <map>


#include <math/mat44.h>

#include <gal/gal.h>

#include <glutpp/gui/object/object.h>




namespace glutpp
{
	class renderable;
	typedef std::shared_ptr<renderable> renderable_p;
	
	namespace gui
	{
		class layout
		{
			public:
				layout();
				std::shared_ptr<glutpp::window>		get_window();
				virtual void				init(renderable_p);
				void					load_xml(char const *);

				void					render(double);
				void					draw();
				
				math::mat44				ortho_;
				
				gal::map<glutpp::gui::object::object>	objects_;

				std::weak_ptr<glutpp::renderable>	renderable_;

				// connections
				struct
				{
					mouse_button_fun_c	mouse_button_fun_;
					key_fun_c		key_fun_;
				} conns_;


				int					key_fun(int,int,int,int);
				int					mouse_button_fun(int,int,int);

				void					connect();
		};
	}
}

#endif
