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
#include <glutpp/actor/actor_base.h>

#include <glutpp/texture.h>
#include <glutpp/material.h>
#include <glutpp/shape/shape.h>
#include <glutpp/network/actor_update.h>

namespace glutpp
{
	namespace actor
	{
		class actor:
			virtual public actor_base
		{
			public:
				actor(
						glutpp::actor::desc_shared,
						std::shared_ptr<glutpp::scene::scene>,
						glutpp::actor::actor_shared = glutpp::actor::actor_shared());

				int		i();
				void		i(int);
				
				void		write_addr(gal::network::message_shared);

				int		i_;

		};
	}
}

#endif
