#ifndef __NEBULA_UI_OBJECT_BASE_HPP__
#define __NEBULA_UI_OBJECT_BASE_HPP__

#include <memory>

#include <boost/signals2.hpp>

#include <tinyxml2.h>

//#include <math/color.hpp>

//#include <galaxy/sig/connection.hpp>

#include <gru/master.hpp>
#include <gru/Color/Color.hpp>

namespace glutpp {
	namespace gui {
		namespace object {
			class Data {
				public:
					Data();

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

					gru::Color::color<float>	font_color_;
					gru::Color::color<float>	bg_color_;

					std::string			label_;

			};
			class object {
				public:

					object();
					void				i(int);
			
					void				init(boost::shared_ptr<glutpp::gui::object::Data>);

					//window::window_s		get_window();
					virtual void			draw() = 0;

					virtual int			key_fun(int,int,int,int) = 0;
					virtual int			mouse_button_fun(int,int,int);
					//virtual void			connect();



					int				i_;



					bool				active_;


					Data				data_;

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

