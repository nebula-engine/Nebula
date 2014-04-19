#ifndef __GLUTPP_CAMERA_H__
#define __GLUTPP_CAMERA_H__

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
		namespace View {
			/** @brief @Base */
			class Base {
				public:
					Base();
					//void		init(glutpp::renderable_shared);
					virtual math::mat44	view() = 0;

					void			load();

					/** @brief step
					 * TODO explain when in timeline this occurs and in which thread and why
					 */
					void		step(float);

					/** TODO is this needed?
					 */
					int		north(float);

					//std::weak_ptr<renderable>		renderable_;

					//math::vec4				eye_;
					/** @brief time of last step */
					double					last_;
			};
		}
	}
}

#endif


