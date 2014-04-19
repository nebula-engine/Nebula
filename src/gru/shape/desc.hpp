#ifndef __GLUTPP_SHAPE_DESC_H__
#define __GLUTPP_SHAPE_DESC_H__

#include <vector>

#include <tinyxml2.h>

#include <math/vec3.hpp>
//#include <math/raw/raw.hpp>

#include <galaxy/network/serial.hpp>

#include <gru/config.hpp>
#include <gru/material.hpp>
//#include <gru/shape/desc.hpp>
#include <gru/light/desc.hpp>

namespace glutpp
{
	namespace shape
	{
		class id: public gal::network::serial<id, gal::network::base> {
			public:
				int i_;
		};


		typedef gal::network::vector_ext<glutpp::shape::desc> vec_shape_desc;
		typedef gal::network::vector_ext<glutpp::light::desc> vec_light_desc;
		
		typedef std::shared_ptr<vec_shape_desc> vec_shape_desc_s;
		typedef std::shared_ptr<vec_light_desc> vec_light_desc_s;
		
		typedef gal::network::serial_ext<id,raw,vec_shape_desc,vec_light_desc>	ser_desc;

		class desc: public ser_desc
		{
			public:
				//typedef gal::network::serial_ext<id,raw,vec_shape_desc,vec_light_desc> SER;

				desc();
				void			load(glutpp::shape::shape_s);
				void			load(tinyxml2::XMLElement*);


				id_s				get_id();
				raw_s				get_raw();
				vec_shape_desc_s		get_shapes();
				vec_light_desc_s		get_lights();
		};
	}
}

#endif



