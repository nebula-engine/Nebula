#ifndef __NEBULA_DESC_LIGHT_H__
#define __NEBULA_DESC_LIGHT_H__

#include <tinyxml2.h>

#include <math/raw/raw.h>
#include <math/vec3.h>
#include <math/vec4.h>
#include <math/color.h>

#include <gal/network/serial.h>

#include <glutpp/config.h>

namespace glutpp
{
	namespace light
	{
		struct raw: gal::network::serial<raw>
		{
			raw();
			void			load(glutpp::light::light_s);
			void			load(tinyxml2::XMLElement*);
			void			print();

			int			i_;
			unsigned int		flag_;
			
			// position
			math::vec4		pos_;

			// colors
			math::color		ambient_;
			math::color		diffuse_;
			math::color		specular_;

			// other properties
			math::vec3      	spot_direction_;
			float			spot_cutoff_;
			float			spot_exponent_;
			float			spot_light_cos_cutoff_;
			float			atten_const_;
			float			atten_linear_;
			float			atten_quad_;
		};

		class id: public gal::network::serial<id>
		{
			public:
				void		load(glutpp::light::light_s);
				int i_;
		};

		class desc: public gal::network::serial_ext<id, raw>
		{
			public:
				desc();
				void		load(glutpp::light::light_s);

				id_s		get_id() { return std::get<0>(tup_); }
				raw_s		get_raw() { return std::get<1>(tup_); }
				
		};
	}
}

#endif

