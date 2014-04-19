#ifndef __GLUTPP_SHAPE_RAW_H__
#define __GLUTPP_SHAPE_RAW_H__

#include <vector>

#include <tinyxml2.h>

#include <math/vec3.hpp>
//#include <math/raw/raw.h>

#include <galaxy/network/serial.hpp>

#include <gru/config.hpp>
#include <gru/material.hpp>
//#include <gru/shape/desc.hpp>

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

				void			box(math::vec3<double>);
				void			box(tinyxml2::XMLElement*);

				void			sphere(float);
				void			sphere(tinyxml2::XMLElement*);


				int			type_;
				unsigned int		flag_;

				math::transform		pose_;
				math::vec3<double>	s_;


				char			image_[max_filename_length];
				char			normal_[max_filename_length];

		};
		
		typedef gal::network::vector<glutpp::material::raw> vec_mat;
		
		typedef std::shared_ptr<vec_mat> vec_mat_s;
		
		class raw: public gal::network::serial_ext<raw_base, vec_mat> {
			public:
				raw&		operator=(raw const &);
				
				void		load(tinyxml2::XMLElement*);

				raw_base_s	get_raw_base() const;
				vec_mat_s	get_vec_mat() const;
				
		};
	}
}

#endif



