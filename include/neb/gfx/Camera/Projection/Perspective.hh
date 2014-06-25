#ifndef __GLUTPP_CAMERA_PROJECTION_H__
#define __GLUTPP_CAMERA_PROJECTION_H__

#include <vector>
#include <memory>

//#include <neb/config.hh>
#include <neb/gfx/util/decl.hpp>
//#include <neb/camera_control.hpp>

namespace neb {
	namespace gfx {
		namespace Camera {
			namespace Projection {
				/** @brief @Base */
				class base {
					public:
						/** @brief Constructor */
						base(sp::shared_ptr<neb::gfx::environ::base>);

						virtual mat4				proj() = 0;
						void					load(sp::shared_ptr<neb::glsl::program> p);
						/** @brief step
						 * @todo explain when in timeline this occurs and in which thread and why
						 */
						void					step(gal::std::timestep const & ts);
					protected:
						/** @brief Parent */
						sp::shared_ptr<neb::gfx::environ::base>		parent_;
				};
				class Perspective: virtual public base {
					public:
						Perspective(sp::shared_ptr<neb::gfx::environ::base>);
						//void		init(neb::renderable_shared);
						virtual mat4				proj();

						/** @brief step */
						void					step(gal::std::timestep const & ts);

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
