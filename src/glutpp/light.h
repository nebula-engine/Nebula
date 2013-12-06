#ifndef __GLUTPP_LIGHT_H__
#define __GLUTPP_LIGHT_H__

#include <GL/glew.h>

#include <glutpp/object.h>
#include <glutpp/camera.h>
#include <glutpp/texture.h>



#include <math/color.h>


namespace glutpp
{
	class light
	{
		public:
			enum
			{
				DIRECTIONAL = 1 << 0
			};
			
			light(window*,int);
			void		init();
			void		updateGL();
			void		load();
			void		draw();
			void		draw_shadow_no_shader();
			void		dim();
			void		RenderShadowPost();
			void		RenderLightPOV();
			
			// camera (position stored here)
			camera		camera_;

			// colors
			math::color	ambient_;
			math::color	diffuse_;
			math::color	specular_;
			
			// other properties
			math::vec3	spot_direction_;
			float		spot_cutoff_;
			float		spot_exponent_;
			float		spot_light_cos_cutoff_;
			float		atten_const_;
			float		atten_linear_;
			float		atten_quad_;
			
			// uniforms
			uniform		uniform_position_;
			uniform		uniform_ambient_;
			uniform		uniform_diffuse_;
			uniform		uniform_specular_;
			uniform		uniform_spot_direction_;
			uniform		uniform_spot_cutoff_;
			uniform		uniform_spot_exponent_;
			uniform		uniform_spot_light_cos_cutoff_;
			uniform		uniform_atten_const_;
			uniform		uniform_atten_linear_;
			uniform		uniform_atten_quad_;
		
			
			texture		texture_shadow_map_;

			window*		window_;
			unsigned int	flags_;
			GLenum		o_;
	};
}

#endif
