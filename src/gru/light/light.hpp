#ifndef __GLUTPP_LIGHT_H__
#define __GLUTPP_LIGHT_H__

#include <GL/glew.h>
#include <GLFW/glfw3.h>

//#include <galaxy/flag.hpp>

#include <gru/config.hpp>
#include <gru/Camera/View/Base.hpp>
#include <gru/texture.hpp>

#include <gru/light/desc.hpp>
#include <gru/light/raw.hpp>

//#include <math/color.hpp>


namespace glutpp {
	namespace light {
		class light: public gal::flag<unsigned int> {
			public:
				
				light(glutpp::shape::shape_s);
				void				i(int);
				void				init(
						/*glutpp::scene::scene_s,*/
						glutpp::light::desc_s);

				virtual void			release();
				virtual void			cleanup();
				void				step(double) {}
				void				load(int, physx::PxMat44);

				void				load_shadow();
				void				draw();
				void				dim();
				void				RenderShadowPost();
				void				RenderLightPOV();


				void				notify_foundation_change_pose();
				physx::PxMat44			get_pose();
				physx::PxVec4			get_pos();
			private:
				unsigned int			f();
				void				f(unsigned int);
			public:

				int				i_;
				raw				raw_;

				texture				texture_shadow_map_;

				//glutpp::scene::scene_w		scene_;
				glutpp::shape::shape_w			shape_;

		};
	}
}

#endif
