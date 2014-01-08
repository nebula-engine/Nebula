#ifndef __GLUTPP_ACTOR_BASE_H__
#define __GLUTPP_ACTOR_BASE_H__
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
#include <glutpp/texture.h>
#include <glutpp/material.h>
#include <glutpp/shape/shape.h>
#include <glutpp/network/actor_update.h>

namespace glutpp
{
	namespace actor
	{
		class actor_base:
			public std::enable_shared_from_this<actor>,
			public gal::flag<unsigned int>
		{
			public:
				typedef std::shared_ptr<gal::network::message> msg_type;

				enum flag
				{
					SHOULD_DELETE = 1 << 0,
					SHOULD_UPDATE = 1 << 1,
				};

				
				math::mat44		get_pose();

				scene::scene_shared	get_scene();

				void			draw(glutpp::window::window_shared);
				void			load_lights(int&);

				virtual void		cleanup();
				virtual void		release();


				msg_type		serialize();
				desc_shared		desc_generate();

				//virtual void	render_reflection();

				void			send_actor_update(
						std::shared_ptr<gal::network::vector<glutpp::actor::raw> >);

			public:

				glutpp::actor::desc_shared	desc_;

				std::weak_ptr<scene::scene>	scene_;
				std::weak_ptr<actor>		actor_;
			protected:
				glutpp::shape::shape_map	shapes_;
				glutpp::actor::actor_map	actors_;
			private:
				unsigned int			f();
				void				f(unsigned int);
		};
	}
}

#endif
