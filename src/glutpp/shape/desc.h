#ifndef __GLUTPP_SHAPE_DESC_H__
#define __GLUTPP_SHAPE_DESC_H__

#include <vector>

#include <tinyxml2.h>

#include <math/vec3.h>
#include <math/raw/raw.h>

#include <gal/network/serial.h>

#include <glutpp/config.h>
#include <glutpp/material.h>
//#include <glutpp/shape/desc.h>
#include <glutpp/light/desc.h>

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



