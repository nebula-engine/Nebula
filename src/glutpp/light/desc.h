#ifndef __NEBULA_DESC_LIGHT_H__
#define __NEBULA_DESC_LIGHT_H__

#include <tinyxml2.h>

#include <math/raw/raw.h>
#include <math/vec3.h>
#include <math/vec4.h>
#include <math/color.h>

#include <gal/network/serializeable.h>

#include <glutpp/config.h>

namespace glutpp
{
	namespace light
	{
		struct raw
		{
			void			reset();
			void			load(tinyxml2::XMLElement*);
			void			print();

			int			i_;
			unsigned int		flag_;
			
			// position
			math::raw::vec4		pos_;

			// colors
			math::raw::color	ambient_;
			math::raw::color	diffuse_;
			math::raw::color	specular_;

			// other properties
			math::raw::vec3      	spot_direction_;
			float			spot_cutoff_;
			float			spot_exponent_;
			float			spot_light_cos_cutoff_;
			float			atten_const_;
			float			atten_linear_;
			float			atten_quad_;
		};
		class desc
		{
			public:
				desc();
				void		load(glutpp::light::light_shared);


				
				void		write(gal::network::message_shared);
				void		read(gal::network::message_shared);
				size_t		size();
				
				int		i_;
				raw		raw_;
		};
	}
}

#endif

