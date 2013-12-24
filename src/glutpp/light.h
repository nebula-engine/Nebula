#ifndef __GLUTPP_LIGHT_H__
#define __GLUTPP_LIGHT_H__

#include <GLFW/glfw3.h>


#include <glutpp/actor.h>
#include <glutpp/camera.h>
#include <glutpp/texture.h>
#include <glutpp/desc_light.h>


#include <math/color.h>


namespace glutpp
{
	class scene;
	class light
	{
		public:
			enum
			{
				POINT,
				DIRECTIONAL,
				SPOT
			};
			
			light();
			void		init(std::shared_ptr<scene>);
			virtual int	release();
			
			void		load_shader(int);

			void		load_shadow();
			void		draw();
			void		dim();
			void		RenderShadowPost();
			void		RenderLightPOV();
			
			math::vec4	get_pose();
			

			int		i_;
			desc_light	desc_;
			
			texture		texture_shadow_map_;

			std::weak_ptr<scene>	scene_;
			std::weak_ptr<actor>	parent_;
			
	};
}

#endif
