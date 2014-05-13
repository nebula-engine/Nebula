#ifndef __GLUTPP_LIGHT_H__
#define __GLUTPP_LIGHT_H__

#include <GL/glew.h>
#include <GLFW/glfw3.h>

//#include <galaxy/flag.hpp>

#include <boost/weak_ptr.hpp>

#include <Nebula/config.hh>
#include <Nebula/Types.hh>
#include <Nebula/Graphics/Camera/View/Base.hh>
#include <Nebula/Graphics/texture.hh>
#include <Nebula/Graphics/Light/desc.hh>
#include <Nebula/Graphics/Light/raw.hh>

//#include <math/color.hpp>

namespace Neb {
	namespace Light {
		class light { //: public gal::flag {
			public:
				
				light(Neb::Shape::Base_w);

				void				i(int const &);
				int const &			i() const;

				void				init(Neb::Light::desc_w);

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
				//gal::flag::flag_type const &		f() const;
				//void					f(gal::flag::flag_type const &);
			public:

				int				i_;
				Raw				raw_;

				texture				texture_shadow_map_;

				//Neb::scene::scene_w		scene_;
				Neb::Light::Util::Parent_w		parent_;

		};
	}
}

#endif
