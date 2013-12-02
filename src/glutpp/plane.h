#ifndef __GLUTPP_PLANE_H__
#define __GLUTPP_PLANE_H__

#include <math/mat44.h>
#include <math/plane.h>

#include <glutpp/object.h>

namespace glutpp
{
	class plane: public object
	{
		public:
			enum
			{
				PLANAR_REFLECTION_STENCIL = 1 << 0
			};

			plane(window*);
			void	draw();
			void	render_reflection();		


			int useTexture;

			//math::mat44	pose_;
			math::plane	plane_;
			math::vec3	parallel_;
			
			unsigned int	flags_;
	};
}

#endif



