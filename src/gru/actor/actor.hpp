#ifndef __GLUTPP_ACTOR_H__
#define __GLUTPP_ACTOR_H__
#include <memory>
#include <vector>
#include <map>

/*
#include <galaxy/flag.hpp>
#include <galaxy/network/message.hpp>
#include <galaxy/network/vector.hpp>

#include <math/vec4.hpp>
#include <math/vec3.hpp>
#include <math/vec2.hpp>
#include <math/geo/polyhedron.hpp>
#include <math/transform.hpp>
*/

#include <gru/config.hpp>
#include <gru/actor/addr.hpp>
#include <gru/actor/raw.hpp>
#include <gru/actor/desc.hpp>
#include <gru/actor/parent.hpp>
#include <gru/texture.hpp>
#include <gru/material.hpp>
#include <gru/shape/shape.hpp>

namespace glutpp {
	namespace actor {
		class actor:
			virtual public glutpp::actor::parent,
			virtual public glutpp::shape::parent,
			public gal::flag<unsigned int>
		{
			public:
				struct flag {
					enum e {
						SHOULD_RELEASE	= 1 << 0,
						SHOULD_UPDATE	= 1 << 1,
						DESTRUCTIBLE    = 1 << 2,
					};
				};



				actor(glutpp::actor::parent_s parent);

				void				i(int ni);
				int				i();

				unsigned int			f();
				void				f(unsigned int flag);

				virtual void			init(glutpp::actor::desc_s desc);
				virtual void			cleanup();
				virtual void			release();
				virtual void			step(double time);

				glutpp::actor::parent_s		getParent();

				physx::PxMat44		getPose();
				physx::PxMat44		getPoseGlobal();
				
				void				set_pose(physx::PxTransform pose);

				void				notify_foundation_change_pose();

				void				load_lights(int&, physx::PxMat44);
				glutpp::scene::scene_s		get_scene();

				void				draw(glutpp::window::window_s, physx::PxMat44);

				virtual glutpp::actor::raw_s	get_raw();


			public:
				glutpp::actor::parent_w		parent_;
				
				gal::map<glutpp::shape::shape>		shapes_;
				gal::map<glutpp::actor::actor>		actors_;



				int		i_;
			protected:
				raw_s		raw_;
		};
	}
}

#endif
