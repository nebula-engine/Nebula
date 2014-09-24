#ifndef __GLUTPP_CAMERA_MANUAL_
#define __GLUTPP_CAMERA_MANUAL

#include <vector>

#include <neb/core/util/typedef.hpp>

#include <neb/gfx/camera/view/Base.hh>

namespace neb {
	namespace gfx {
		namespace camera {
			namespace view {
				/** @brief free flying camera
				 * this camera can move freely through the scene
				 * user input in interpreted as three-component velocity and yaw and pitch rate
				 */
				class manual:
					virtual public neb::gfx::camera::view::base
				{
					public:
						/** @name constructors
						 * @{
						 */
						manual(std::shared_ptr<neb::gfx::environ::base> parent);
						//Free(math::vec3<double> eye, double yaw, double pitch);
						/** @} */

						/** @brief view matrix */
						virtual mat4					view();
						virtual void					step(gal::etc::timestep const & ts);

						void						init();
						
						vec3						eye_;
						vec3						center_;
						vec3						up_;
				};
			}
		}
	}
}
#endif



