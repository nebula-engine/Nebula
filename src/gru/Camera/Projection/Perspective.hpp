#ifndef __GLUTPP_CAMERA_H__
#define __GLUTPP_CAMERA_H__

#include <vector>
#include <memory>

#include <galaxy/sig/connection.hpp>

#include <math/vec3.hpp>
#include <math/vec4.hpp>
#include <math/mat44.hpp>

#include <gru/config.hpp>
#include <gru/camera_control.hpp>

namespace glutpp {
	/** @brief @camera
	 * defines view space, clip space, and projection for opengl rendering
	 * shall be derived to implement custom behavior such as user control
	 */
	class camera {
		public:
			camera();
			//void		init(glutpp::renderable_shared);
			virtual math::mat44	proj() = 0;
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

			/** @brief field of view angle */
			float					fovy_;
			/** @brief near clipping plane */
			float					zn_;
			/** @brief far clipping plane */
			float					zf_;
			/** @brief width of render context
			 * TODO remove this and h_ from this class
			 * TODO should be accessed by accessing parent context or scene or view object
			 */
			int					w_;
			int					h_;

			//math::vec4				eye_;
			
			/** @brief object for controlling camera properties
			 * TODO determine if this should be done using inheritance instead or explain here why not
			 */
			std::shared_ptr<camera_control>		control_;
	};
}

#endif
