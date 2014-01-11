#ifndef __NEBULA_ACTOR_DESC_H__
#define __NEBULA_ACTOR_DESC_H__

#include <math/transform.h>
#include <math/raw/raw.h>

#include <gal/network/serial.h>

#include <glutpp/actor/id.h>
#include <glutpp/shape/desc.h>

namespace glutpp {
	namespace actor {

		typedef gal::network::vector_ext<glutpp::actor::desc> vec_actor_desc;
		typedef gal::network::vector_ext<glutpp::shape::desc> vec_shape_desc;
		typedef std::shared_ptr<vec_actor_desc> vec_actor_desc_s;
		typedef std::shared_ptr<vec_shape_desc> vec_shape_desc_s;


		struct desc: gal::network::serial_ext<vec_shape_desc, vec_actor_desc, raw, id>
		{

			void			load(glutpp::actor::actor_s);
			void			load(tinyxml2::XMLElement*);
			void			add_shape(glutpp::shape::desc);



			id_s			get_id();

			raw_s			get_raw();

			vec_actor_desc_s	get_actors();
			vec_shape_desc_s	get_shapes();

		};
	}
}

#endif








