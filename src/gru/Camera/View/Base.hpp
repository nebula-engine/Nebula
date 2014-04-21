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
					struct Flag {
						enum E {
							NORTH = 1<<0,
							SOUTH = 1<<1,
							EAST = 1<<2,
							WEST = 1<<3
						};
					};

					Base();
					
					//void		init(glutpp::renderable_shared);
					virtual math::mat44	view() = 0;
					
					void			load();
					
					/** @brief step
					 * TODO explain when in timeline this occurs and in which thread and why
					 */
					virtual void		Step(double) = 0;


					//std::weak_ptr<renderable>		renderable_;

					//math::vec4				eye_;
					/** @brief time of last step */
					double					last_;
			};
		}
	}
}

#endif


