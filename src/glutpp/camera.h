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
			camera();
			math::mat44	proj();
			math::mat44	view();
			void		load();
			

			float		fovy_;
			float		zn_;
			float		zf_;
			int		w_;
			int		h_;

			math::vec4	eye_;
			math::vec3	center_;
			math::vec3	up_;

	};
}

#endif
