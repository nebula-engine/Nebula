#ifndef __GLUTPP_LIGHT_H__
#define __GLUTPP_LIGHT_H__

#include <GL/glew.h>
#include <GLFW/glfw3.h>


//#include <galaxy/flag.hpp>

#include <boost/archive/polymorphic_iarchive.hpp>
#include <boost/archive/polymorphic_oarchive.hpp>

#include <Nebula/config.hh>
#include <Nebula/Types.hh>


#include <Nebula/Math/Serialization/GLM.hpp>

#include <Nebula/Graphics/Light/__base.hpp>
#include <Nebula/Graphics/Light/Util/Flag.hh>
#include <Nebula/Graphics/Light/Util/Types.hh>
#include <Nebula/Graphics/Light/Util/light_count.hpp>

#include <Nebula/Graphics/texture.hh>
#include <Nebula/Graphics/Color/Color.hh>
#include <Nebula/Util/typedef.hpp>

//#include <math/color.hpp>

namespace neb {
	namespace Light {
		class base: virtual public neb::core::light::__base {
			public:
				base(sp::shared_ptr<neb::Light::util::parent> parent, ::std::string);
				
				void				init();
				
				virtual void			release();
				virtual void			cleanup();
				virtual void			step(neb::core::TimeStep const & ts);

				virtual void			load(neb::core::light::util::count & light_count, mat4) = 0;
				void				load(int o, mat4);

				void				load_shadow();
				void				draw();
				void				dim();
				void				RenderShadowPost();
				void				RenderLightPOV();


				glm::mat4x4			get_pose();
				glm::vec4			get_pos();
			private:
				template<class Archive> void		serializeTemplate(Archive & ar, unsigned int const & version) {
					ar & boost::serialization::make_nvp("i",i_);
					ar & boost::serialization::make_nvp("flag",flag_);
					ar & boost::serialization::make_nvp("pos",pos_);
					ar & boost::serialization::make_nvp("ambient",ambient_);
					ar & boost::serialization::make_nvp("diffuse",diffuse_);
					ar & boost::serialization::make_nvp("specular",specular_);
/*					ar & boost::serialization::make_nvp("atten_const",atten_const_);
					ar & boost::serialization::make_nvp("atten_linear",atten_linear_);
					ar & boost::serialization::make_nvp("atten_quad",atten_quad_);*/
				}
			public:
				virtual void				serialize(boost::archive::polymorphic_iarchive & ar, unsigned int const & version) {
					serializeTemplate(ar, version);
				}
				virtual void				serialize(boost::archive::polymorphic_oarchive & ar, unsigned int const & version) {
					serializeTemplate(ar, version);
				}
			public:
				sp::shared_ptr<neb::Light::util::parent>	parent_;

				neb::Light::util::Flag				flag_;

				::std::string					light_type_string_;

				// position
				glm::vec3					pos_;

				// colors
				neb::Color::color<float>			ambient_;
				neb::Color::color<float>			diffuse_;
				neb::Color::color<float>			specular_;

				// other properties


				texture						texture_shadow_map_;


		};
	}
}

#endif
