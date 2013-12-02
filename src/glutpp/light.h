#ifndef __GLUTPP_LIGHT_H__
#define __GLUTPP_LIGHT_H__

#include <GL/gl.h>

#include <math/color.h>

#include <glutpp/object.h>
#include <glutpp/camera.h>
#include <glutpp/texture.h>

namespace glutpp
{
	class light: public glutpp::object
	{
		public:
			enum
			{
				DIRECTIONAL = 1 << 0
			};

			light(window*,GLenum);	
			void		updateGL();
			void		draw();
			void		dim();
			void		RenderShadow();
			void		RenderShadowPost();
			void		RenderLightPOV();
			
			camera		camera_;

			// colors
			math::color	ambient_;
			math::color	diffuse_;
			math::color	specular_;

			
			texture		texture_shadow_map_;

			unsigned int	flags_;
			GLenum		o_;
	};
}

#endif
