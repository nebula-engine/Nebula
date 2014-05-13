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
#include <Nebula/Graphics/glsl/program.hh>

namespace Neb {
	namespace Camera {
		namespace View {
			/** @brief @Base */
			class Base {
				public:
					/** @brief Constructor */
					Base() {}
					/** @brief Load view matrix into GLSL. */
					void				load();
					/** @brief Get view matrix. */
					virtual physx::PxMat44	view() = 0;
					/** @brief Step.
					 * @todo explain when in timeline this occurs and in which thread and why
					 */
					virtual void			step(double) = 0;
					/** @brief Time of last step */
					double				last_;
			};
		}
	}
}

#endif


