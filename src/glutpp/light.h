#ifndef __GLUTPP_LIGHT_H__
#define __GLUTPP_LIGHT_H__

#include <math/color.h>

#include <glutpp/camera.h>

namespace glutpp
{
	class light
	{
		public:
			enum
			{
				DIRECTIONAL = 1 << 0
			};

			camera		camera_;
			math::color	color_;
			unsigned int	flags_;
	};
}

#endif
