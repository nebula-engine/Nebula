#ifndef __GLUTPP_LIGHT_RAW_H__
#define __GLUTPP_LIGHT_RAW_H__

#include <tinyxml2.h>

//#include <math/raw/raw.hpp>
#include <math/vec3.hpp>
#include <math/vec4.hpp>
#include <math/color.hpp>

#include <galaxy/network/serial.hpp>

#include <gru/config.hpp>

namespace glutpp
{
	namespace light
	{
		class raw: public gal::network::serial<raw, gal::network::base> {
			public:
				//typedef glutpp::light::light<raw>	LIGHT;
				//typedef std::shared_ptr<LIGHT>	LIGHT_S;
				
				raw();
				void			load(glutpp::light::light_s);
				void			load(tinyxml2::XMLElement*);
				void			print();

				int			i_;
				unsigned int		flag_;

				// position
				math::vec4<double>		pos_;

				// colors
				math::Color::color<double>	ambient_;
				math::Color::color<double>	diffuse_;
				math::Color::color<double>	specular_;

				// other properties
				math::vec3<double>     	spot_direction_;
				double			spot_cutoff_;
				double			spot_exponent_;
				double			spot_light_cos_cutoff_;
				double			atten_const_;
				double			atten_linear_;
				double			atten_quad_;
		};
	}
}

#endif

