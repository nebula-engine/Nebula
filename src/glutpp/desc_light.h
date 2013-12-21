#ifndef __NEBULA_DESC_LIGHT_H__
#define __NEBULA_DESC_LIGHT_H__

#include <tinyxml2.h>

#include <math/vec3.h>
#include <math/vec4.h>
#include <math/color.h>

namespace glutpp
{
	struct desc_light
	{
		desc_light();
		void		load(tinyxml2::XMLElement*);

		math::vec4	pos_;

		// colors
		math::color     ambient_;
		math::color     diffuse_;
		math::color     specular_;

		// other properties
		math::vec3      spot_direction_;
		float           spot_cutoff_;
		float           spot_exponent_;
		float           spot_light_cos_cutoff_;
		float           atten_const_;
		float           atten_linear_;
		float           atten_quad_;
	};
}

#endif

