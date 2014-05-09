#ifndef __GLUTPP_LIGHT_H__
#define __GLUTPP_LIGHT_H__

#include <GL/glew.h>
#include <GLFW/glfw3.h>

//#include <galaxy/flag.hpp>

#include <boost/weak_ptr.hpp>

#include <Nebula/config.hpp>
#include <Nebula/Types.hpp>
#include <Nebula/Graphics/Camera/View/Base.hpp>
#include <Nebula/Graphics/texture.hpp>
#include <Nebula/Graphics/light/desc.hpp>
#include <Nebula/Graphics/light/raw.hpp>

//#include <math/color.hpp>


namespace Neb {
	namespace light {
		class light: public gal::flag {
			public:
				
				light(boost::shared_ptr<Neb::Shape::shape>);

				void				i(int const &);
				int const &			i() const;

				void				init(Neb::light::desc_w);

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
				gal::flag::flag_type		f();
				void				f(gal::flag::flag_type);
			public:

				int				i_;
				raw				raw_;

				texture				texture_shadow_map_;

				//Neb::scene::scene_w		scene_;
				boost::weak_ptr<Neb::Shape::shape>			shape_;

		};
	}
}

#endif
