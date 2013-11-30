#ifndef __GLUTPP_CAMERA_H__
#define __GLUTPP_CAMERA_H__

namespace glutpp
{
	class camera
	{
		public:
			math::vec3	eye;
			math::vec3	center;
			math::vec3	up;

			math::mat44	proj;
			math::mat44	view;
	};
}

#endif
