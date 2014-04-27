#ifndef __GLUTPP_CAMERA_H__
#define __GLUTPP_CAMERA_H__

#include <vector>
#include <memory>

#include <galaxy/sig/connection.hpp>

#include <math/vec3.hpp>
#include <math/vec4.hpp>
#include <math/mat44.hpp>

#include <gru/config.hpp> //<gru/config.hpp.in>
//#include <gru/camera_control.hpp>
#include <gru/master.hpp>
#include <gru/glsl/program.hpp>

namespace glutpp {
	namespace Camera {
		namespace View {
			/** @brief @Base */
			template<typename MATRIX_T, typename TIME_T = double> class Base {
				public:
					/** @brief Constructor */
					Base() {}
					/** @brief Load view matrix into GLSL. */
					void				load() {
						auto p = glutpp::master::Global()->get_program(glutpp::program_name::e::LIGHT);
						
						p->get_uniform_scalar("view")->load(view());
					}
					/** @brief Get view matrix. */
					virtual math::mat44<MATRIX_T>	view() = 0;
					/** @brief Step.
					 * @todo explain when in timeline this occurs and in which thread and why
					 */
					virtual void			step(TIME_T) = 0;
					/** @brief Time of last step */
					TIME_T				last_;
			};
		}
	}
}

#endif


