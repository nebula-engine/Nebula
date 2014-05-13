#ifndef __GLUTPP_CAMERA_PROJECTION_H__
#define __GLUTPP_CAMERA_PROJECTION_H__

#include <vector>
#include <memory>

#include <Nebula/config.hpp>
//#include <Nebula/camera_control.hpp>

namespace Neb {
	namespace Camera {
		namespace Projection {
			/** @brief @Base */
			class Base {
				public:
					/** @brief Constructor */
					Base(std::shared_ptr<Neb::renderable>);
					
					virtual physx::PxMat44			proj() = 0;
					void					load();
					/** @brief step
					 * @todo explain when in timeline this occurs and in which thread and why
					 */
					void					step(double);

					/** @name Accessors @{ */
					/** @brief Get parent window */
					Neb::window::window_s		getWindow();
					/** @} */
				protected:
					/** @brief Parent */
					std::weak_ptr<renderable>		renderable_;
			};
			class Perspective: public Base {
				public:
					Perspective(std::shared_ptr<Neb::renderable>);
					//void		init(Neb::renderable_shared);
					virtual physx::PxMat44			proj();


					/** @brief step */
					void					step(double);

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
