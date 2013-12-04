#ifndef __GLUTPP_SPHERE_H__
#define __GLUTPP_SPHERE_H__

#include <math/mat44.h>
#include <math/plane.h>

#include <glutpp/object.h>

namespace glutpp
{
	class sphere: public object
	{
		public:
			sphere();
			void	draw();

	};
}

#endif



