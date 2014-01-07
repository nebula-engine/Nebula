#ifndef __GLUTPP_SHAPE_DESC_H__
#define __GLUTPP_SHAPE_DESC_H__

#include <vector>

#include <tinyxml2.h>

#include <math/vec3.h>
#include <math/raw/raw.h>

#include <glutpp/config.h>
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
				enum
				{
					max_filename_length = 20
				};
				
				void			reset();
				void			load(tinyxml2::XMLElement*);
				void			parse_type(char const *);

				void			box(math::vec3);
				void			box(tinyxml2::XMLElement*);

				void			sphere(float);
				void			sphere(tinyxml2::XMLElement*);


				int			type_;
				int			i_;
				unsigned int		flag_;
				math::raw::transform	pose_;
				math::raw::vec3		s_;

				glutpp::material_desc	front_;

				glutpp::program_name::e	program_;

				char			image_[max_filename_length];
				char			normal_[max_filename_length];

				unsigned int		shape_size_;
				unsigned int		light_size_;
		};
		class desc
		{
			public:
				desc();
				void			reset();
				void			load(tinyxml2::XMLElement*);

				
				size_t			size();
				void			write(char*&);
				void			read(char*&);
				


				raw						raw_;

				std::vector<glutpp::shape::desc_shared>		shapes_;
				std::vector<glutpp::light::desc_shared>		lights_;
		};
	}
}

#endif



