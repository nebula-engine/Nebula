#ifndef __NEB_CAMERA_RIDEALONG_H__
#define __NEB_CAMERA_RIDEALONG_H__

#include <memory>
#include <map>

#include <Nebula/core/actor/Util/Types.hh>
#include <Nebula/gfx/window/Base.hh>
#include <Nebula/gfx/Camera/View/Base.hh>
#include <Nebula/config.hh>

namespace neb {
	namespace gfx {
		namespace Camera {
			namespace View {
				class Ridealong: public neb::gfx::Camera::View::base {
					public:
						Ridealong(sp::shared_ptr<neb::gfx::environ::base>);

						virtual mat4				view();
						virtual void				step(neb::core::TimeStep const & ts);


						sp::weak_ptr<neb::core::actor::base>	actor_;
				};
			}
		}
	}
}
#endif


