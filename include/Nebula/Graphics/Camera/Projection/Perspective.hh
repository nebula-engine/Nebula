#ifndef __GLUTPP_CAMERA_PROJECTION_H__
#define __GLUTPP_CAMERA_PROJECTION_H__

#include <vector>
#include <memory>

#include <Nebula/config.hh>
#include <Nebula/Graphics/Types.hh>
//#include <Nebula/camera_control.hpp>

namespace neb {
	namespace gfx {
		namespace Camera {
			namespace Projection {
				/** @brief @Base */
				class base {
					public:
						/** @brief Constructor */
						Base(sp::shared_ptr<neb::gfx::context::base>);

						virtual mat4				proj() = 0;
						void					load(sp::shared_ptr<neb::glsl::program> p);
						/** @brief step
						 * @todo explain when in timeline this occurs and in which thread and why
						 */
						void					step(neb::core::TimeStep const & ts);
					protected:
						/** @brief Parent */
						sp::shared_ptr<neb::gfx::context::base>		parent_;
				};
				class Perspective: public Base {
					public:
						Perspective(sp::shared_ptr<neb::gfx::context::base>);
						//void		init(neb::renderable_shared);
						virtual mat4				proj();

						/** @brief step */
						void					step(neb::core::TimeStep const & ts);

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
