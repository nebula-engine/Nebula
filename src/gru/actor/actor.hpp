#ifndef __GLUTPP_ACTOR_H__
#define __GLUTPP_ACTOR_H__
#include <memory>
#include <vector>
#include <map>

#include <gal/flag.h>
#include <gal/network/message.h>
#include <gal/network/vector.h>

#include <math/vec4.h>
#include <math/vec3.h>
#include <math/vec2.h>
#include <math/geo/polyhedron.h>
#include <math/transform.h>

#include <gru/config.hpp>
#include <gru/actor/addr.hpp>
#include <gru/actor/raw.hpp>
#include <gru/actor/desc.hpp>
#include <gru/parent.hpp>
#include <gru/texture.hpp>
#include <gru/material.hpp>
#include <gru/shape/shape.hpp>

namespace glutpp { namespace actor {
	class actor: public glutpp::parent, public gal::flag<unsigned int> {
		public:
			struct flag {
				enum e {
					SHOULD_RELEASE	= 1 << 0,
					SHOULD_UPDATE	= 1 << 1,
					DESTRUCTIBLE    = 1 << 2,
				};
			};



			actor(glutpp::parent_s parent);

			void				i(int ni);
			int				i();

			unsigned int			f();
			void				f(unsigned int flag);

			virtual void			init(glutpp::actor::desc_s desc);
			virtual void			cleanup();
			virtual void			release();
			virtual void			step(double time);

			math::mat44			get_pose();
			void				set_pose(math::transform pose);

			void				notify_foundation_change_pose();

			void				load_lights(int&, math::mat44);
			glutpp::scene::scene_s		get_scene();

			void				draw(glutpp::window::window_s, math::mat44);

			virtual glutpp::actor::raw_s	get_raw();
		public:

			gal::map<glutpp::shape::shape>		shapes_;
			gal::map<glutpp::actor::actor>		actors_;



			int		i_;
		protected:
			raw_s		raw_;
	};
}
}

#endif
