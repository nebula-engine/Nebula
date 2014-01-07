#ifndef __NEBULA_DESC_LIGHT_H__
#define __NEBULA_DESC_LIGHT_H__

#include <tinyxml2.h>

#include <math/raw/raw.h>
#include <math/vec3.h>
#include <math/vec4.h>
#include <math/color.h>

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

				size_t		size();
				void		write(char*&);
				void		read(char*&);




				raw		raw_;

		};
	}
}

#endif

