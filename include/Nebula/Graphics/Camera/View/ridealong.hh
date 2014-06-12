#ifndef __NEB_CAMERA_RIDEALONG_H__
#define __NEB_CAMERA_RIDEALONG_H__

#include <memory>
#include <map>

#include <Nebula/Actor/Util/Types.hh>
#include <Nebula/Graphics/Window/Base.hh>
#include <Nebula/Graphics/Camera/View/Base.hh>
#include <Nebula/config.hh>

namespace neb {
	namespace gfx {
		namespace Camera {
			namespace View {
				class Ridealong: public neb::gfx::Camera::View::Base {
					public:
						Ridealong(sp::shared_ptr<neb::gfx::Context::Base>;

						virtual mat4				view();
						virtual void				step(neb::core::TimeStep const & ts);


						sp::shared_ptr<neb::Actor::Base>	actor_;
				};
			}
		}
	}
}
#endif


