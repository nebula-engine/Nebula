#ifndef __GLUTPP_CAMERA_CONROL_H__
#define __GLUTPP_CAMERA_CONROL_H__

#include <vector>

#include <Nebula/Util/typedef.hpp>
#include <Nebula/Graphics/Camera/View/Base.hh>

namespace neb {
	namespace gfx {
		namespace Camera {
			namespace View {
				/** @brief free flying camera
				 * this camera can move freely through the scene
				 * user input in interpreted as three-component velocity and yaw and pitch rate
				 */
				class Free: public Neb::Graphics::Camera::View::Base {
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
						Free(Neb::Graphics::Context::Base_s parent);
						//Free(math::vec3<double> eye, double yaw, double pitch);
						/** @} */

						/** @brief view matrix */
						virtual mat4					view();
						virtual void					step(Neb::Core::TimeStep const & ts);

						void						init();

						float						pitch_;
						float						yaw_;

						vec4						eye_;
						vec3						center_;
						vec3						look_;
						vec3						up_;

						vec3						v0_;
						vec3						v1_;

						//std::vector<gal::sig::connection<>*>		vec_x_;
						//std::vector<gal::sig::connection<>*>		vec_y_;
						//std::vector<gal::sig::connection<>*>		vec_z_;

						Neb::Graphics::Window::Base_w			window_;


						std::map<int,unsigned int>			key_flag_;
						std::map<int,vec3>				head_;
						std::map<unsigned int,int>			head_flag_;
				};
			}
		}
	}
}
#endif



