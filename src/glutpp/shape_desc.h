#ifndef __GLUTPP_SHAPE_DESC_H__
#define __GLUTPP_SHAPE_DESC_H__

#include <tinyxml2.h>

#include <math/vec3.h>
#include <math/raw/raw.h>

#include <glutpp/material.h>

namespace glutpp
{
	struct shape_desc
	{
		void			reset();

		void			parse_xml(tinyxml2::XMLElement*);
		void			parse_type(char const *);


		int			box(math::vec3);
		int			box(tinyxml2::XMLElement*);

		int			sphere(float);
		int			sphere(tinyxml2::XMLElement*);


		int			type_;
		math::raw::vec3		s_;
		
		glutpp::material_desc	front_;
	};
}


#endif
