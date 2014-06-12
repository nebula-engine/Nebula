#ifndef __GLUTPP_CAMERA_H__
#define __GLUTPP_CAMERA_H__

#include <vector>
#include <memory>

//#include <galaxy/sig/connection.hpp>

/*
#include <math/vec3.hpp>
#include <math/vec4.hpp>
#include <math/mat44.hpp>
*/

#include <Nebula/Types.hh>
#include <Nebula/Core/TimeStep.hpp>
#include <Nebula/Graphics/Types.hh>

namespace neb {
	namespace gfx {
		namespace Camera {
			namespace View {
				/** @brief @Base */
				class Base {
					public:
						/** @brief Constructor */
						Base(sp::shared_ptr<neb::gfx::Context::Base> parent);
						/** @brief Load view matrix into GLSL. */
						void					load(sp::shared_ptr<neb::glsl::program> p);
						/** @brief Get view matrix. */
						virtual glm::mat4			view() = 0;
						/** @brief Step
						 *
						 * @todo explain when in timeline this occurs and in which thread and why
						 */
						virtual void				step(neb::core::TimeStep const & ts) = 0;
						sp::shared_ptr<neb::gfx::Context::Base>		parent_;
				};
			}
		}
	}
}

#endif


