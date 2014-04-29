#ifndef __GLUTPP_SCENE_H__
#define __GLUTPP_SCENE_H__

#include <vector>

#include <gru/Flag.hpp>
#include <gru/Map.hpp>

#include <gru/config.hpp>
#include <gru/glsl/program.hpp>
#include <gru/scene/raw.hpp>
#include <gru/actor/actor.hpp>
#include <gru/Camera/View/Base.hpp>

//#include <glutpp/shader.h>

#define LIGHT_MAX 20

namespace glutpp {
	namespace scene {
		class less_str {
			public:
				bool operator()(char* s0, char* s1) {
					assert(s0);
					assert(s1);

					if(*s0 < *s1) return true;

					if(*s0 == *s1)
					{
						if(*s0 == 0)
						{
							return false;
						}
						else
						{
							return operator()(s0+1, s1+1);
						}
					}

					return false;

				}
		};

		typedef std::map<char*, glutpp::actor::desc_s, less_str> actors_deferred_map;

		class scene:
			public glutpp::actor::parent,
			public gal::flag<unsigned int>
		{
			public:
				struct Flag {
					enum e {
						RAY_TRACE			= 1 << 0,
						LIGHTING			= 1 << 1,
						SHADOW				= 1 << 2,
						REFLECT				= 1 << 4,
						REFLECT_PLANAR			= 1 << 5,
						REFLECT_CURVED			= 1 << 6,
						TEX_IMAGE			= 1 << 7,
						TEX_NORMAL_MAP			= 1 << 8,
						SHADER				= 1 << 9
					};
				};

				scene();
				~scene();
				void			i(int ni);
				int			i();
				unsigned int		f();
				void			f(unsigned int flag);
				void			init(glutpp::scene::desc_s desc);
				void			release();
				physx::PxMat44	get_pose();
				/** @brief render */
				void			render(
						double time,
						std::shared_ptr<glutpp::Camera::View::Base<float> >,
						std::shared_ptr<glutpp::Camera::Projection::Base>,
						glutpp::window::window_s);
				void			draw(glutpp::window::window_s window);
				void			resize(int w, int h);


			public:
				int					i_;
				boost::shared_ptr<raw>			raw_;

				renderable_w				renderable_;

				Neb::Map<glutpp::actor::actor>		actors_;
				actors_deferred_map			actors_deferred_;
		};
	}
}

#endif





