#ifndef __GLUTPP_MATERIAL_H__
#define __GLUTPP_MATERIAL_H__

#include <tinyxml2.h>

#include <math/raw/raw.h>
#include <math/color.h>

namespace glutpp
{
	class window;
	struct material_desc
	{
		void		load(tinyxml2::XMLElement*);

		math::raw::color	ambient_;
		math::raw::color	diffuse_;
		math::raw::color	specular_;
		math::raw::color	emission_;

	};
	class material
	{
		public:
			material();
			void		init();
			void		load();
			void		load(glutpp::material_desc);
			
			math::color		ambient_;
			math::color		diffuse_;
			math::color		specular_;
			math::color		emission_;
			float			shininess_;
	};
}

#endif
