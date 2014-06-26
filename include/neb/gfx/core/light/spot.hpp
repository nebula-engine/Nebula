#ifndef NEBULA_LIGHT_SPOT_HH
#define NEBULA_LIGHT_SPOT_HH

#include <GL/glew.h>
#include <GLFW/glfw3.h>

//#include <galaxy/flag.hpp>

#include <boost/archive/polymorphic_iarchive.hpp>
#include <boost/archive/polymorphic_oarchive.hpp>

#include <neb/util/config.hh>
#include <neb/util/decl.hpp>
#include <neb/util/shared.hpp>

#include <neb/math/Serialization/GLM.hpp>

#include <neb/gfx/core/light/base.hpp>

#include <neb/gfx/texture.hh>
#include <neb/core/light/base.hpp>


//#include <math/color.hpp>

namespace neb { namespace gfx { namespace core { namespace light {


		class spot: public neb::gfx::core::light::base {
			private:
				template<class Archive> void		serializeTemplate(Archive & ar, unsigned int const & version) {


					ar & boost::serialization::make_nvp("spot_direction",spot_direction_);
					ar & boost::serialization::make_nvp("spot_cutoff",spot_cutoff_);
					ar & boost::serialization::make_nvp("spot_exponent",spot_exponent_);
					ar & boost::serialization::make_nvp("spot_light_cos_cutoff",spot_light_cos_cutoff_);
				}
			public:
				spot(sp::shared_ptr<neb::core::light::util::parent> parent);

				virtual void				load(neb::core::light::util::count & light_count, neb::core::pose const & pose);

				virtual void			serialize(boost::archive::polymorphic_iarchive & ar, unsigned int const & version) {
					neb::gfx::core::light::base::serialize(ar, version);
					serializeTemplate(ar, version);
				}
				virtual void			serialize(boost::archive::polymorphic_oarchive & ar, unsigned int const & version) {
					neb::gfx::core::light::base::serialize(ar, version);
					serializeTemplate(ar, version);
				}	

				

				vec3				spot_direction_;
				float				spot_cutoff_;
				float				spot_exponent_;
				float				spot_light_cos_cutoff_;

				float				atten_const_;
				float				atten_linear_;
				float				atten_quad_;


		};

}}}}

#endif
