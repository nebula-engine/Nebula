#ifndef __GLUTPP_LIGHT_H__
#define __GLUTPP_LIGHT_H__

#include <GL/gl.h>

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

			light(GLenum);	
			void		updateGL();

			
			camera		camera_;

			math::color	ambient_;
			math::color	diffuse_;
			math::color	specular_;

			unsigned int	flags_;
			GLenum		o_;
	};
}

#endif
