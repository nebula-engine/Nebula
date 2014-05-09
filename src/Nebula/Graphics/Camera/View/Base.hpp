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

#include <Nebula/config.hpp> //<gru/config.hpp.in>
//#include <Nebula/camera_control.hpp>
#include <Nebula/master.hpp>
#include <Nebula/Graphics/glsl/program.hpp>

namespace Neb {
	namespace Camera {
		namespace View {
			/** @brief @Base */
			class Base {
				public:
					/** @brief Constructor */
					Base() {}
					/** @brief Load view matrix into GLSL. */
					void				load() {
						auto p = Neb::master::global()->get_program(Neb::program_name::e::LIGHT);
						
						p->get_uniform_scalar("view")->load(view());
					}
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


