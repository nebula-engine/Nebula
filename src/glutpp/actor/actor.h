#ifndef __GLUTPP_ACTOR_H__
#define __GLUTPP_ACTOR_H__
#include <memory>
#include <vector>
#include <map>

#include <gal/flag.h>

#include <math/vec4.h>
#include <math/vec3.h>
#include <math/vec2.h>
#include <math/geo/polyhedron.h>
#include <math/transform.h>

#include <glutpp/config.h>
#include <glutpp/texture.h>
#include <glutpp/material.h>
#include <glutpp/shape/shape.h>

namespace glutpp
{
	namespace actor
	{
		class actor: public std::enable_shared_from_this<actor>, public gal::flag
		{
			public:
				enum flag
				{
					SHOULD_DELETE = 1 << 0
				};

				actor(
						glutpp::actor::desc*,
						std::shared_ptr<glutpp::scene>,
						glutpp::actor::actor_shared = glutpp::actor::actor_shared());

				math::mat44		get_pose();

				std::shared_ptr<scene>	get_scene();

				void			draw(std::shared_ptr<glutpp::window>);
				void			load_lights(int&);

				virtual void		cleanup();
				virtual void		release();

				//virtual void	render_reflection();

				int			i_;
				
				
				
				glutpp::actor::desc*	desc_;

				std::weak_ptr<scene>	scene_;
				std::weak_ptr<actor>	actor_;
			protected:
				shape_vec		shapes_;
			public:
				actor_vec		actors_;

		};
	}
}

#endif
