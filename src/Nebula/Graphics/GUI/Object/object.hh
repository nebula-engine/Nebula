#ifndef __NEBULA_UI_OBJECT_BASE_HPP__
#define __NEBULA_UI_OBJECT_BASE_HPP__

#include <memory>

#include <boost/signals2.hpp>

#include <Nebula/Util/Shared.hh>
#include <Nebula/Graphics/Color/Color.hh>

namespace Neb {
	namespace GUI {
		namespace Object {
			class Base: virtual public Neb::Util::Shared {
				public:

					Base();
			
					void				init();

					//window::window_s		get_window();
					virtual void			draw() = 0;

					virtual int			key_fun(int,int,int,int) = 0;
					virtual int			mouse_button_fun(int,int,int);
					//virtual void			connect();




					bool				active_;


					template<class Archive> void	serialize(Archive & ar, unsigned int const & version) {
						ar & boost::serialization::make_nvp("x",x_);
						ar & boost::serialization::make_nvp("y",y_);
						ar & boost::serialization::make_nvp("w",w_);
						ar & boost::serialization::make_nvp("h",h_);
						ar & boost::serialization::make_nvp("font_color",font_color_);
						ar & boost::serialization::make_nvp("bg_color",bg_color_);
						ar & boost::serialization::make_nvp("label",label_);

					}

					float				x_;
					float				y_;
					float				w_;
					float				h_;

					Neb::Color::color<float>	font_color_;
					Neb::Color::color<float>	bg_color_;

					std::string			label_;
					// connections
					struct
					{
						boost::signals2::connection		mouse_button_fun_;
						boost::signals2::connection		key_fun_;
					} conns_;



			};
		}
	}
}
#endif

