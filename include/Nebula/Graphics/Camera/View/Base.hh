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
#include <Nebula/Graphics/glsl/program.hh>

namespace Neb {
	namespace Graphics {
		namespace Camera {
			namespace View {
				/** @brief @Base */
				class Base {
					public:
						/** @brief Constructor */
						Base(Neb::Graphics::Context::Base_s parent);
						/** @brief Load view matrix into GLSL. */
						void					load();
						/** @brief Get view matrix. */
						virtual glm::mat4			view() = 0;
						/** @brief Step
						 *
						 * @todo explain when in timeline this occurs and in which thread and why
						 */
						virtual void				step(Neb::Core::TimeStep const & ts) = 0;
						Neb::Graphics::Context::Base_s		parent_;
				};
			}
		}
	}
}

#endif


