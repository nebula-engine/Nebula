#ifndef __GLUTPP_CAMERA_CONROL_H__
#define __GLUTPP_CAMERA_CONROL_H__

#include <vector>

#include <Nebula/util/typedef.hpp>
#include <Nebula/gfx/Camera/View/Base.hh>

namespace neb {
	namespace gfx {
		namespace Camera {
			namespace View {
				/** @brief free flying camera
				 * this camera can move freely through the scene
				 * user input in interpreted as three-component velocity and yaw and pitch rate
				 */
				class Free: public neb::gfx::Camera::View::base {
					public:
						/** @name constructors
						 * @{
						 */
						Free(sp::shared_ptr<neb::gfx::environ::base> parent);
						//Free(math::vec3<double> eye, double yaw, double pitch);
						/** @} */

						/** @brief view matrix */
						virtual mat4					view();
						virtual void					step(neb::core::TimeStep const & ts);

						void						init();
						


						virtual void						connect(
								sp::shared_ptr<neb::gfx::window::base> const & window);
						int						key_fun(
								sp::shared_ptr<neb::gfx::window::base> const & window,
								int key,
								int scancode,
								int action,
								int mods);


						vec3						move();

			
						
						float						pitch_;
						float						yaw_;

						vec4						eye_;
						vec3						center_;
						vec3						look_;
						vec3						up_;



						int						key_n_;
						int						key_s_;
						int						key_e_;
						int						key_w_;
						int						key_u_;
						int						key_d_;
						int						key_yaw_pos_;
						int						key_yaw_neg_;
						int						key_pitch_pos_;
						int						key_pitch_neg_;


						::std::map<int,unsigned int>			key_flag_;
						::std::map<int,vec3>				head_;
						::std::map<unsigned int,int>			head_flag_;
				};
			}
		}
	}
}
#endif



