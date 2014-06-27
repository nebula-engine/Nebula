#ifndef __GLUTPP_GFX_LIGHT_H__
#define __GLUTPP_GFX_LIGHT_H__

#include <GL/glew.h>
#include <GLFW/glfw3.h>


//#include <galaxy/flag.hpp>

#include <boost/archive/polymorphic_iarchive.hpp>
#include <boost/archive/polymorphic_oarchive.hpp>

//#include <neb/config.hh>
#include <neb/util/decl.hpp>


#include <neb/math/Serialization/GLM.hpp>

#include <neb/core/light/base.hpp>

#include <neb/gfx/texture.hh>
#include <neb/gfx/Color/Color.hh>
#include <neb/util/typedef.hpp>

//#include <math/color.hpp>

namespace neb { namespace gfx { namespace core { namespace light {

		class base: virtual public neb::core::light::base {
			public:
				base(sp::shared_ptr<neb::core::light::util::parent> parent, ::std::string);
				
				void				init();
				
				virtual void			release();
				virtual void			cleanup();
				virtual void			step(gal::std::timestep const & ts);

				virtual void			load(neb::core::light::util::count & light_count, neb::core::pose const & pose) = 0;
				void				load(int o, neb::core::pose const & pose);

				void				load_shadow();
				void				draw();
				void				dim();
				void				RenderShadowPost();
				void				RenderLightPOV();


				neb::core::pose			getPose();
				vec4				getPos();
			private:
				template<class Archive> void		serializeTemplate(Archive & ar, unsigned int const & version) {
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
			
				::std::string					light_type_string_;

				// colors
				neb::Color::color<float>			ambient_;
				neb::Color::color<float>			diffuse_;
				neb::Color::color<float>			specular_;

				// other properties

				texture						texture_shadow_map_;


		};

}}}}

#endif
