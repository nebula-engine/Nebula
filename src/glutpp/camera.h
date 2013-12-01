#ifndef __GLUTPP_CAMERA_H__
#define __GLUTPP_CAMERA_H__

#include <math/vec3.h>
#include <math/vec4.h>
#include <math/mat44.h>

namespace glutpp
{
	class camera
	{
		public:
			math::vec4	eye_;
			math::vec3	center_;
			math::vec3	up_;

			math::mat44	proj_;
			math::mat44	view_;
			
			void		update_matrix();
	};
}

#endif
