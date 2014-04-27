#ifndef __GLUTPP_MATERIAL_H__
#define __GLUTPP_MATERIAL_H__

#include <tinyxml2.h>

//#include <math/raw/raw.h>
#include <math/color.hpp>

namespace glutpp {
	namespace material {


		struct raw
		{
			raw();
			void				load(tinyxml2::XMLElement*);

			math::Color::color<float>	ambient_;
			math::Color::color<float>	diffuse_;
			math::Color::color<float>	specular_;
			math::Color::color<float>	emission_;
			float				shininess_;
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
