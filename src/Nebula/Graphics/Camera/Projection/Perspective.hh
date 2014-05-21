#ifndef __GLUTPP_CAMERA_PROJECTION_H__
#define __GLUTPP_CAMERA_PROJECTION_H__

#include <vector>
#include <memory>

#include <Nebula/config.hh>
//#include <Nebula/camera_control.hpp>

namespace Neb {
	namespace Graphics {
		namespace Camera {
			namespace Projection {
				/** @brief @Base */
				class Base {
					public:
						/** @brief Constructor */
						Base(Neb::Graphics::Context::Base_s);

						virtual physx::PxMat44			proj() = 0;
						void					load();
						/** @brief step
						 * @todo explain when in timeline this occurs and in which thread and why
						 */
						void					step(double);

						/** @name Accessors @{ */
						/** @brief Get parent window */
						Neb::Graphics::Window::Base_s		getWindow();
						/** @} */
					protected:
						/** @brief Parent */
						Neb::Graphics::Context::Base_s		parent_;
				};
				class Perspective: public Base {
					public:
						Perspective(Neb::Graphics::Context::Base_s);
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
}
#endif
