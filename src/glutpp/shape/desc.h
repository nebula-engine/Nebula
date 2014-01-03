#ifndef __GLUTPP_SHAPE_DESC_H__
#define __GLUTPP_SHAPE_DESC_H__

#include <vector>

#include <tinyxml2.h>

#include <math/vec3.h>
#include <math/raw/raw.h>

#include <glutpp/material.h>
#include <glutpp/shape/desc.h>
#include <glutpp/light/desc.h>

namespace glutpp
{
	namespace shape
	{
		struct raw
		{
			public:
				void			reset();
				void			load(tinyxml2::XMLElement*);
				void			parse_type(char const *);

				void			box(math::vec3);
				void			box(tinyxml2::XMLElement*);

				void			sphere(float);
				void			sphere(tinyxml2::XMLElement*);


				int			type_;
				math::raw::transform	pose_;
				math::raw::vec3		s_;

				glutpp::material_desc	front_;

		};
		class desc
		{
			public:
				void			reset();
				void			load(tinyxml2::XMLElement*);

				


				
				
				raw					raw_;
				
				std::vector<glutpp::shape::desc*>	shapes_;
				std::vector<light::desc*>		lights_;
		};
	}
}

#endif



