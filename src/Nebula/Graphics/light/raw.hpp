#ifndef __GLUTPP_LIGHT_RAW_H__
#define __GLUTPP_LIGHT_RAW_H__

#include <tinyxml2.h>

/*
//#include <math/raw/raw.hpp>
#include <math/vec3.hpp>
#include <math/vec4.hpp>
#include <math/color.hpp>
*/
//#include <galaxy/network/serial.hpp>

#include <Nebula/Types.hpp>
#include <Nebula/Math/Typedef.hpp>
#include <Nebula/Graphics/Color/Color.hpp>

namespace Neb {
	namespace light {
		class raw {
			public:
				//typedef Neb::light::light<raw>	LIGHT;
				//typedef std::shared_ptr<LIGHT>	LIGHT_S;
				
				raw();
				void			load(Neb::light::light_w);
				//void			load(tinyxml2::XMLElement*);
				
				template<class Archive> void	serialize(Archive& ar, unsigned int const & version) {
					ar & boost::serialization::make_nvp("i",i_);
					ar & boost::serialization::make_nvp("flag",flag_);
					ar & boost::serialization::make_nvp("pos",pos_);
					ar & boost::serialization::make_nvp("ambient",ambient_);
					ar & boost::serialization::make_nvp("diffuse",diffuse_);
					ar & boost::serialization::make_nvp("specular",specular_);
					ar & boost::serialization::make_nvp("spot_direction",spot_direction_);
					ar & boost::serialization::make_nvp("spot_cutoff",spot_cutoff_);
					ar & boost::serialization::make_nvp("spot_exponent",spot_exponent_);
					ar & boost::serialization::make_nvp("spot_light_cos_cutoff",spot_light_cos_cutoff_);
					ar & boost::serialization::make_nvp("atten_const",atten_const_);
					ar & boost::serialization::make_nvp("atten_linear",atten_linear_);
					ar & boost::serialization::make_nvp("atten_quad",atten_quad_);
				}


				void				print();

				int				i_;
				Neb::Light::Flag		flag_;

				// position
				Neb::Math::Vec4			pos_;

				// colors
				Neb::Color::color<float>	ambient_;
				Neb::Color::color<float>	diffuse_;
				Neb::Color::color<float>	specular_;

				// other properties
				physx::PxVec3     	spot_direction_;
				float			spot_cutoff_;
				float			spot_exponent_;
				float			spot_light_cos_cutoff_;
				float			atten_const_;
				float			atten_linear_;
				float			atten_quad_;
		};
	}
}

#endif

