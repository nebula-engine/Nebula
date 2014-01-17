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

#include <glutpp/texture.h>
#include <glutpp/material.h>
#include <glutpp/shape/shape.h>

namespace glutpp
{
	namespace actor
	{
		class actor:
			public std::enable_shared_from_this<actor>,
			public gal::flag<unsigned int>

		{
			public:

				actor(
						glutpp::scene::scene_s,
						glutpp::actor::actor_s = glutpp::actor::actor_s());



				math::mat44		get_pose();

				scene::scene_s		get_scene();

				void			draw(glutpp::window::window_s);
				void			load_lights(int&);

				virtual void		cleanup();
				virtual void		release();


			public:


				scene::scene_w		scene_;
				actor_w			actor_;


				glutpp::shape::shape_m		shapes_;
				glutpp::actor::actor_m		actors_;
			private:
				unsigned int			f();
				void				f(unsigned int);



			public:

				void		init(glutpp::actor::desc_s);

				int		i();
				void		i(int);

				void		write_addr(gal::network::message_shared);

				int		i_;
				raw		raw_;
		};
	}
}

#endif
