#ifndef __NEB_CAMERA_RIDEALONG_H__
#define __NEB_CAMERA_RIDEALONG_H__

#include <memory>
#include <map>

#include <Nebula/Graphics/window/window.hpp>
#include <Nebula/Graphics/Camera/View/Base.hpp>
#include <Nebula/config.hpp>

namespace Neb {
	namespace Camera {
		namespace View {
			class Ridealong: public Neb::Camera::View::Base {
				public:
					Ridealong(Neb::Actor::Base_w);

					virtual physx::PxMat44			view();
					virtual void				step(double time);


					Neb::Actor::Base_w		actor_;
			};
		}
	}
}

#endif


