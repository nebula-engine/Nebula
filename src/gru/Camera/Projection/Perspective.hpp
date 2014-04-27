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
					/** @brief Constructor */
					Base(std::shared_ptr<glutpp::renderable>);
					
					virtual math::mat44<float>		proj() = 0;
					void					load();
					/** @brief step
					 * @todo explain when in timeline this occurs and in which thread and why
					 */
					void					step(double);

					/** @name Accessors @{ */
					/** @brief Get parent window */
					glutpp::window::window_s		getWindow();
					/** @} */
				protected:
					/** @brief Parent */
					std::weak_ptr<renderable>		renderable_;
			};
			class Perspective: public Base {
				public:
					Perspective(std::shared_ptr<glutpp::renderable>);
					//void		init(glutpp::renderable_shared);
					virtual math::mat44<float>	proj();


					/** @brief step */
					void		step(double);

					//

					/** @brief field of view angle */
					float					fovy_;
					/** @brief near clipping plane */
					float					zn_;
					/** @brief far clipping plane */
					float					zf_;

			};
		}
	}
}
#endif
