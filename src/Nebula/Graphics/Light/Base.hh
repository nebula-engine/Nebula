#ifndef __GLUTPP_LIGHT_H__
#define __GLUTPP_LIGHT_H__

#include <GL/glew.h>
#include <GLFW/glfw3.h>

//#include <galaxy/flag.hpp>

#include <boost/archive/polymorphic_iarchive.hpp>
#include <boost/archive/polymorphic_oarchive.hpp>

#include <Nebula/config.hh>
#include <Nebula/Types.hh>
#include <Nebula/Util/Shared.hh>

#include <Nebula/Math/Serialization.hh>

#include <Nebula/Graphics/Light/Util/Flag.hh>
#include <Nebula/Graphics/Light/Util/Types.hh>

#include <Nebula/Graphics/texture.hh>
#include <Nebula/Graphics/Color/Color.hh>


//#include <math/color.hpp>

namespace Neb {
	namespace Light {
		class Base: virtual public Neb::Util::Shared {
			public:
				Base();
				Base(Neb::Light::Util::Parent_s);
				
				void				init();
				
				virtual void			release();
				virtual void			cleanup();
				void				step(double const & time, double const & dt);
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
				template<class Archive> void		serializeTemplate(Archive & ar, unsigned int const & version) {
					ar & boost::serialization::make_nvp("i",i_);
					ar & boost::serialization::make_nvp("flag",flag_);
					ar & boost::serialization::make_nvp("pos",pos_);
					ar & boost::serialization::make_nvp("ambient",ambient_);
					ar & boost::serialization::make_nvp("diffuse",diffuse_);
					ar & boost::serialization::make_nvp("specular",specular_);
					ar & boost::serialization::make_nvp("atten_const",atten_const_);
					ar & boost::serialization::make_nvp("atten_linear",atten_linear_);
					ar & boost::serialization::make_nvp("atten_quad",atten_quad_);
				}
			public:
				virtual void		load(boost::archive::polymorphic_iarchive & ar, unsigned int const & version) {
					serializeTemplate(ar, version);
					loadLightBase(ar, version);
				}
				virtual void		save(boost::archive::polymorphic_oarchive & ar, unsigned int const & version) {
					serializeTemplate(ar, version);
					saveLightBase(ar, version);
				}
				virtual void		loadLightBase(boost::archive::polymorphic_iarchive & ar, unsigned int const & version) = 0;
				virtual void		saveLightBase(boost::archive::polymorphic_oarchive & ar, unsigned int const & version) = 0;
			public:
				Neb::Light::Util::Parent_s	parent_;

				Neb::Light::Util::Flag		flag_;

				// position
				physx::PxVec4			pos_;

				// colors
				Neb::Color::color<float>	ambient_;
				Neb::Color::color<float>	diffuse_;
				Neb::Color::color<float>	specular_;

				// other properties

				float				atten_const_;
				float				atten_linear_;
				float				atten_quad_;




				texture				texture_shadow_map_;


		};
	}
}

#endif
