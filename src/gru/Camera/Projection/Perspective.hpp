#ifndef __GLUTPP_CAMERA_PROJECTION_H__
#define __GLUTPP_CAMERA_PROJECTION_H__

#include <vector>
#include <memory>

#include <galaxy/sig/connection.hpp>

#include <math/vec3.hpp>
#include <math/vec4.hpp>
#include <math/mat44.hpp>

#include <gru/config.hpp>
//#include <gru/camera_control.hpp>

namespace glutpp {
	namespace Camera {
		namespace Projection {
			/** @brief @Base */
			class Base {
				public:
					Base();

					virtual math::mat44	proj() = 0;
					void			load();
					/** @brief step
					 * TODO explain when in timeline this occurs and in which thread and why
					 */
					void			step(float);

					/** @name
					 * @{
					 */
					/** @brief access parent */
					glutpp::window::window_s&		getWindow();
					/** @} */

					/** @brief field of view angle */
					float					fovy_;
					/** @brief near clipping plane */
					float					zn_;
					/** @brief far clipping plane */
					float					zf_;
					/** @brief width of render context
					 * TODO remove this and h_ from this class
					 * TODO should be accessed by accessing parent context or scene or view object
					 */

			};
			class Perspective: public Base {
				public:
					Perspective();
					//void		init(glutpp::renderable_shared);
					virtual math::mat44	proj() = 0;


					/** @brief step */
					void		step(float);

					//std::weak_ptr<renderable>		renderable_;



			};
		}
	}
}
#endif
