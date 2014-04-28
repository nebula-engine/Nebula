#ifndef __GLUTPP_LIGHT_RAW_H__
#define __GLUTPP_LIGHT_RAW_H__

#include <tinyxml2.h>

/*
//#include <math/raw/raw.hpp>
#include <math/vec3.hpp>
#include <math/vec4.hpp>
#include <math/color.hpp>
*/
#include <galaxy/network/serial.hpp>

#include <gru/config.hpp>

namespace glutpp {
	namespace light {
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
				physx::PxVec4		pos_;

				// colors
				gru::Color::color<float>	ambient_;
				gru::Color::color<float>	diffuse_;
				gru::Color::color<float>	specular_;

				// other properties
				physx::PxVec3     	spot_direction_;
				float			spot_cutoff_;
				float			spot_exponent_;
				float			spot_light_cos_cutoff_;
				float			atten_const_;
				float			atten_linear_;
				float			atten_quad_;
		};
	}
}

#endif

