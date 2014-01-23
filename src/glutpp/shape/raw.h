#ifndef __GLUTPP_SHAPE_RAW_H__
#define __GLUTPP_SHAPE_RAW_H__

#include <vector>

#include <tinyxml2.h>

#include <math/vec3.h>
#include <math/raw/raw.h>

#include <gal/network/serial.h>

#include <glutpp/config.h>
#include <glutpp/material.h>
//#include <glutpp/shape/desc.h>

namespace glutpp
{
	namespace shape
	{
		class raw_base: public gal::network::serial<raw, gal::network::base> {
			public:
				enum
				{
					max_filename_length = 20
				};

				raw_base();
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


				char			image_[max_filename_length];
				char			normal_[max_filename_length];

		};
		
		typedef gal::network::vector<glutpp::material::raw> vec_mat;
		
		typedef std::shared_ptr<vec_mat> vec_mat_s;
		
		class raw: public gal::network::serial_ext<raw_base, vec_mat> {
			public:
				void		load(tinyxml2::XMLElement*);

				raw_base_s	get_raw_base();
				vec_mat_s	get_vec_mat();
				
		};
	}
}

#endif



