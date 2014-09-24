#ifndef __NEB_CAMERA_RIDEALONG_H__
#define __NEB_CAMERA_RIDEALONG_H__

#include <memory>
#include <map>

#include <neb/core/core/actor/util/decl.hpp>
#include <neb/gfx/window/Base.hh>
#include <neb/gfx/camera/view/Base.hh>
//#include <neb/config.hh>

namespace neb {
	namespace gfx {
		namespace camera {
			namespace view {
				class ridealong: public neb::gfx::camera::view::base {
					public:
						ridealong(
								std::shared_ptr<neb::gfx::environ::base>,
								std::weak_ptr<neb::core::core::actor::base> actor);
						
						virtual glm::mat4				view();
						
						virtual void					step(gal::etc::timestep const & ts);

						std::weak_ptr<neb::core::core::actor::base>	actor_;
				};
			}
		}
	}
}


#endif


