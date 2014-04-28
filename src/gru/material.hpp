#ifndef __GLUTPP_MATERIAL_H__
#define __GLUTPP_MATERIAL_H__

#include <tinyxml2.h>

//#include <math/raw/raw.h>
//#include <math/color.hpp>

#include <gru/Color/Color.hpp>

namespace glutpp {
	namespace material {


		struct raw
		{
			raw();
			raw(tinyxml2::XMLElement*);

			
			template<class Archive> void	serialize(Archive & ar) {
				ar & ambient_;
				ar & diffuse_;
				ar & specular_;
				ar & emission_;
				ar & shininess_;
			}

			gru::Color::color<float>	ambient_;
			gru::Color::color<float>	diffuse_;
			gru::Color::color<float>	specular_;
			gru::Color::color<float>	emission_;
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
