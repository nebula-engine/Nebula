#ifndef __GLUTPP_MATERIAL_H__
#define __GLUTPP_MATERIAL_H__

#include <tinyxml2.h>

#include <math/raw/raw.h>
#include <math/color.h>

namespace glutpp {
	namespace material {


		struct raw
		{
			raw();
			void			load(tinyxml2::XMLElement*);

			math::color		ambient_;
			math::color		diffuse_;
			math::color		specular_;
			math::color		emission_;
			float			shininess_;
		};

		class material
		{
			public:
				material();
				void		init();
				void		load();
				void		step(double);

				raw		raw_;
		};
	}
}

#endif
