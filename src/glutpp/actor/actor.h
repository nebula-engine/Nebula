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

#include <glutpp/config.h>

#include <glutpp/actor/addr.h>
#include <glutpp/actor/raw.h>
#include <glutpp/actor/desc.h>

#include <glutpp/parent.h>
#include <glutpp/texture.h>
#include <glutpp/material.h>
#include <glutpp/shape/shape.h>

namespace glutpp {
	namespace actor {
		class actor: public glutpp::parent, public gal::flag<unsigned int> {

			public:
				actor(glutpp::parent_s parent);
				
				void			i(int ni);
				int			i();
		
				unsigned int		f();
				void			f(unsigned int flag);
		
				void			init(glutpp::actor::desc_s desc);
				void			cleanup();
				void			release();
				void			step(double time);

				math::mat44		get_pose();
				void			set_pose(math::transform pose);

				void			notify_foundation_change_pose();

				void			load_lights(int&, math::mat44);
				glutpp::scene::scene_s	get_scene();
				
				void			draw(glutpp::window::window_s, math::mat44);


				gal::map<glutpp::shape::shape>		shapes_;
				gal::map<glutpp::actor::actor>		actors_;
				
				glutpp::actor::raw_s		get_raw() { assert(raw_); return raw_; }
				
				int		i_;
			protected:
				raw_s		raw_;
		};
	}
}

#endif
