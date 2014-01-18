#ifndef __GLUTPP_SHAPE_DESC_H__
#define __GLUTPP_SHAPE_DESC_H__

#include <vector>

#include <tinyxml2.h>

#include <math/vec3.h>
#include <math/raw/raw.h>

#include <gal/network/serial.h>

#include <glutpp/config.h>
#include <glutpp/material.h>
#include <glutpp/shape/desc.h>
#include <glutpp/light/desc.h>

namespace glutpp
{
	namespace shape
	{
		struct raw: gal::network::serial<raw> {
			enum
			{
				max_filename_length = 20
			};

			raw();
			void			load(tinyxml2::XMLElement*);
			void			parse_type(char const *);

			void			box(math::vec3);
			void			box(tinyxml2::XMLElement*);

			void			sphere(float);
			void			sphere(tinyxml2::XMLElement*);


			int			type_;
			unsigned int		flag_;
			
			math::transform		pose_;
			math::vec3		s_;
			
			glutpp::material_desc	front_;
			
			glutpp::program_name::e	program_;

			char			image_[max_filename_length];
			char			normal_[max_filename_length];
		};
		
		struct id: gal::network::serial<id>
		{
			int i_;
		};
		
		typedef gal::network::vector_ext<glutpp::shape::desc> vec_shape_desc;
		typedef gal::network::vector_ext<glutpp::light::desc> vec_light_desc;
		
		typedef std::shared_ptr<vec_shape_desc> vec_shape_desc_s;
		typedef std::shared_ptr<vec_light_desc> vec_light_desc_s;
		
		struct desc: gal::network::serial_ext<vec_light_desc, vec_shape_desc, raw, id>
		{
		
			desc();
			void			load(glutpp::shape::shape_s);
			void			load(tinyxml2::XMLElement*);
			
			
			std::shared_ptr<id>	get_id();
			std::shared_ptr<raw>	get_raw();
			vec_shape_desc_s	get_shapes();
			vec_light_desc_s	get_lights();
		};
	}
}

#endif



