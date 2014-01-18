#ifndef __NEBULA_ACTOR_RAW_H__
#define __NEBULA_ACTOR_RAW_H__

#include <math/transform.h>
#include <math/raw/raw.h>

#include <gal/network/serial.h>

#include <glutpp/shape/desc.h>

namespace glutpp {
	namespace actor {
		struct filter_data {
			unsigned int word0;
			unsigned int word1;
			unsigned int word2;
			unsigned int word3;
		};
		struct raw: gal::network::serial<raw> {
			enum
			{
				max_name_length = 31
			};
			
			raw();
			void			load(tinyxml2::XMLElement*);
			void			plane(tinyxml2::XMLElement*);
			void			controller(tinyxml2::XMLElement*);




			glutpp::actor::type		type_;
			glutpp::actor::mode_create::e	mode_create_;
			unsigned int			flag_;
			char				name_[32];

			math::transform		pose_;

			math::vec3		n_;
			float			d_;

			math::vec3		velocity_;
			float			density_;

			struct {
				filter_data	simulation_;
				filter_data	scene_query_;
			} filter_data_;
		};



		class event: public gal::network::serial<event> {
			public:
				glutpp::actor::type_event::e	type_;
		};
	}
}

#endif








