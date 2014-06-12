#ifndef NEBULA_LIGHT_SPOT_HH
#define NEBULA_LIGHT_SPOT_HH

#include <GL/glew.h>
#include <GLFW/glfw3.h>

//#include <galaxy/flag.hpp>

#include <boost/archive/polymorphic_iarchive.hpp>
#include <boost/archive/polymorphic_oarchive.hpp>

#include <Nebula/config.hh>
#include <Nebula/Types.hh>
#include <Nebula/Util/shared.hpp>

#include <Nebula/Math/Serialization/GLM.hpp>

#include <Nebula/Graphics/Light/Util/Flag.hh>
#include <Nebula/Graphics/Light/Util/Types.hh>

#include <Nebula/Graphics/texture.hh>
#include <Nebula/Graphics/Light/Base.hh>


//#include <math/color.hpp>

namespace neb {
	namespace Light {
		class Point: public Neb::Light::Base {
			public:
				Point(sp::shared_ptr<Neb::Light::Util::Parent> parent): Neb::Light::Base(parent) {}

				virtual void				load(int o, mat4 space);


		};
		class Spot: public Neb::Light::Base {
			private:
				template<class Archive> void		serializeTemplate(Archive & ar, unsigned int const & version) {
					ar & boost::serialization::make_nvp("spot_direction",spot_direction_);
					ar & boost::serialization::make_nvp("spot_cutoff",spot_cutoff_);
					ar & boost::serialization::make_nvp("spot_exponent",spot_exponent_);
					ar & boost::serialization::make_nvp("spot_light_cos_cutoff",spot_light_cos_cutoff_);
				}
			public:
				Spot(sp::shared_ptr<Neb::Light::Util::Parent> parent);

				virtual void				load(int o, mat4 space);

				virtual void			serialize(boost::archive::polymorphic_iarchive & ar, unsigned int const & version) {
					Neb::Light::Base::serialize(ar, version);
					serializeTemplate(ar, version);
				}
				virtual void			serialize(boost::archive::polymorphic_oarchive & ar, unsigned int const & version) {
					Neb::Light::Base::serialize(ar, version);
					serializeTemplate(ar, version);
				}	


				vec3				spot_direction_;
				float				spot_cutoff_;
				float				spot_exponent_;
				float				spot_light_cos_cutoff_;
		};
		class Directional: public Neb::Light::Base {
			public:
		};
	}
}

#endif
