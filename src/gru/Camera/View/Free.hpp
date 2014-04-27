#ifndef __GLUTPP_CAMERA_CONROL_H__
#define __GLUTPP_CAMERA_CONROL_H__

#include <vector>

#include <PxPhysicsAPI.h>

#include <math/vec3.hpp>

#include <galaxy/sig/connection.hpp>

#include <gru/Camera/View/Base.hpp>

namespace glutpp {
	namespace Camera {
		namespace View {
			/** @brief free flying camera
			 * this camera can move freely through the scene
			 * user input in interpreted as three-component velocity and yaw and pitch rate
			 */
			class Free: public Base<float> {
				public:
					/** @brief Map. */
					struct Flag {
						enum E {
							NORTH = 1<<0,
							SOUTH = 1<<1,
							EAST = 1<<2,
							WEST = 1<<3
						};
					};

					/** @name constructors
					 * @{
					 */
					Free();
					//Free(math::vec3<double> eye, double yaw, double pitch);
					/** @} */

					/** @brief view matrix */
					virtual math::mat44<float>			view();
					virtual void					step(double);
					
					void						init(glutpp::window::window_s);

					float						pitch_;
					float						yaw_;

					math::vec4<float>				eye_;
					math::vec3<float>				center_;
					math::vec3<float>				look_;
					math::vec3<float>				up_;

					math::vec3<float>				v0_;
					math::vec3<float>				v1_;

					std::vector<gal::sig::connection<>*>		vec_x_;
					std::vector<gal::sig::connection<>*>		vec_y_;
					std::vector<gal::sig::connection<>*>		vec_z_;

					glutpp::window::window_w				window_;


					std::map<int,unsigned int>		key_flag_;
					std::map<int,physx::PxVec3>		head_;
					std::map<unsigned int,int>		head_flag_;
			};
		}
	}
}
#endif



