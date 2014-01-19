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
			desc();
			template<typename ACTOR> void load(std::shared_ptr<ACTOR> actor) {
				GLUTPP_DEBUG_0_FUNCTION;

				get_id()->i_ = actor->i_;

				*get_raw() = actor->raw_;

				// shape
				glutpp::shape::desc_s sd;
				for(auto it = actor->shapes_.begin(); it != actor->shapes_.end(); ++it)
				{
					auto shape = it->second;

					sd.reset(new glutpp::shape::desc);

					sd->load(shape);

					get_shapes()->vec_.push_back(std::make_tuple(sd));
				}

				// actor
				glutpp::actor::desc_s ad;
				for(auto it = actor->actors_.begin(); it != actor->actors_.end(); ++it)
				{
					auto a = it->second;

					ad.reset(new glutpp::actor::desc);

					ad->load(a);

					get_actors()->vec_.push_back(std::make_tuple(ad));
				}




			}
			void			load(tinyxml2::XMLElement*);
			void			add_shape(glutpp::shape::desc);

			desc&			operator=(desc const &);


			id_s			get_id() const;
			raw_s			get_raw() const;
			vec_actor_desc_s	get_actors() const;
			vec_shape_desc_s	get_shapes() const;


		};
	}
}

#endif








