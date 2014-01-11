#ifndef __NEBULA_ACTOR_RAW_H__
#define __NEBULA_ACTOR_RAW_H__

#include <math/transform.h>
#include <math/raw/raw.h>

#include <gal/network/serial.h>

#include <glutpp/shape/desc.h>

namespace glutpp {
	namespace actor {
		enum type {
			NONE = 0,
			BASE,
			ACTOR,
			RIGID_ACTOR,
			RIGID_BODY,
			RIGID_DYNAMIC,
			RIGID_STATIC,
			PLANE,
			CONTROLLER,
			EMPTY
		};
		struct filter_data {
			unsigned int word0;
			unsigned int word1;
			unsigned int word2;
			unsigned int word3;
		};
		struct raw: gal::network::serial<raw> {
	
			raw();
			void			load(tinyxml2::XMLElement*);
			void			plane(tinyxml2::XMLElement*);
			void			controller(tinyxml2::XMLElement*);




			glutpp::actor::type	type_;

			math::transform		pose_;

			math::vec3		n_;
			float			d_;

			math::vec3		velocity_;
			float			density_;

			unsigned int		flag_;

			struct {
				filter_data	simulation_;
				filter_data	scene_query_;
			} filter_data_;
		};
	}
}

#endif








