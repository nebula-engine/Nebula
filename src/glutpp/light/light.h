#ifndef __GLUTPP_LIGHT_H__
#define __GLUTPP_LIGHT_H__

#include <GLFW/glfw3.h>

#include <glutpp/config.h>
#include <glutpp/actor/actor.h>
#include <glutpp/camera.h>
#include <glutpp/texture.h>

#include <glutpp/light/desc.h>


#include <math/color.h>


namespace glutpp
{
	namespace light
	{
		enum
		{
			light_max = 20
		};
		class light: public gal::flag<unsigned int>
		{
			public:
				enum type
				{
					POINT,
					DIRECTIONAL,
					SPOT
				};
				enum flag
				{
					SHOULD_DELETE = 1 << 0
				};

				light(glutpp::shape::shape_shared);
				void				i(int);
				void				init(
						glutpp::scene::scene_shared,
						glutpp::light::desc_shared);

				virtual void			release();
				virtual void			cleanup();

				void				load(int);

				void				load_shadow();
				void				draw();
				void				dim();
				void				RenderShadowPost();
				void				RenderLightPOV();


				math::mat44			get_pose();
				math::vec4			get_pos();

				desc_shared			desc_generate();
			private:
				unsigned int			f();
				void				f(unsigned int);
			public:

				int				i_;
				raw				raw_;

				texture				texture_shadow_map_;

				glutpp::scene::scene_weak	scene_;
				glutpp::shape::shape_weak	shape_;

		};
	}
}

#endif
