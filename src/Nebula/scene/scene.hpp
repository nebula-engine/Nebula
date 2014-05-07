#ifndef __GLUTPP_SCENE_H__
#define __GLUTPP_SCENE_H__

#include <vector>

#include <Nebula/Flag.hpp>
#include <Nebula/Map.hpp>

#include <Nebula/config.hpp> // Nebula/config.hpp.in
#include <Nebula/Graphics/glsl/program.hpp>
#include <Nebula/scene/raw.hpp>
#include <Nebula/Actor/Base.hpp>
#include <Nebula/Graphics/Camera/View/Base.hpp>

//#include <glutpp/shader.h>

#define LIGHT_MAX 20

namespace Neb {
	namespace Scene {
		class scene: public Neb::Actor::parent, public gal::flag<unsigned int> {
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
				void				i(int ni);
				int				i();
				unsigned int			f();
				void				f(unsigned int flag);
				void				init(Neb::Scene::desc_w desc);
				void				release();
				physx::PxMat44			get_pose();
				/** @brief render */
				void				render(
						double time,
						std::shared_ptr<Neb::Camera::View::Base>,
						std::shared_ptr<Neb::Camera::Projection::Base>,
						Neb::window::window_s);
				void				draw(Neb::window::window_s window);
				void				resize(int w, int h);


			public:
				int									i_;
				boost::shared_ptr<raw>							raw_;

				Neb::weak_ptr<Neb::renderable>						renderable_;

				Neb::Map<Neb::Actor::Base>						actors_;
				std::map<std::string, boost::shared_ptr<Neb::Actor::desc> >		actors_deferred_;
		};
	}
}

#endif





