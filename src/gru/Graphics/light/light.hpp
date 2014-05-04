#ifndef __GLUTPP_LIGHT_H__
#define __GLUTPP_LIGHT_H__

#include <GL/glew.h>
#include <GLFW/glfw3.h>

//#include <galaxy/flag.hpp>

#include <boost/weak_ptr.hpp>

#include <gru/config.hpp>
#include <gru/Graphics/Camera/View/Base.hpp>
#include <gru/Graphics/texture.hpp>

#include <gru/Graphics/light/desc.hpp>
#include <gru/Graphics/light/raw.hpp>

//#include <math/color.hpp>


namespace glutpp {
	namespace light {
		class light: public gal::flag<unsigned int> {
			public:
				
				light(boost::shared_ptr<glutpp::shape::shape>);
				void				i(int);
				void				init(boost::shared_ptr<glutpp::light::desc>);

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
				boost::weak_ptr<glutpp::shape::shape>			shape_;

		};
	}
}

#endif
