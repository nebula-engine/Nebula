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

			math::Color::color<double>	ambient_;
			math::Color::color<double>	diffuse_;
			math::Color::color<double>	specular_;
			math::Color::color<double>	emission_;
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
