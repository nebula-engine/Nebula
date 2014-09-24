#ifndef __GLUTPP_CAMERA_CONROL_H__
#define __GLUTPP_CAMERA_CONROL_H__

#include <vector>

#include <neb/core/util/typedef.hpp>
#include <neb/core/input/sink.hpp>

#include <neb/gfx/camera/view/Base.hh>

namespace neb {
	namespace gfx {
		namespace camera {
			namespace view {
				/** @brief free flying camera
				 * this camera can move freely through the scene
				 * user input in interpreted as three-component velocity and yaw and pitch rate
				 */
				class Free:
					virtual public neb::core::input::sink,
					virtual public neb::gfx::camera::view::base
				{
					public:
						/** @name constructors
						 * @{
						 */
						Free(std::shared_ptr<neb::gfx::environ::base> parent);
						//Free(math::vec3<double> eye, double yaw, double pitch);
						/** @} */

						/** @brief view matrix */
						virtual mat4					view();
						virtual void					step(gal::etc::timestep const & ts);

						void						init();
						


						virtual void					connect(
								std::shared_ptr<neb::core::input::source> const &);
						virtual int					keyFun(
								std::shared_ptr<neb::core::input::source> const &,
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



