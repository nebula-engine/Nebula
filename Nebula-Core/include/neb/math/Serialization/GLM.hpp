#ifndef NEBULA_SERIALIZATION_GLM_HPP
#define NEBULA_SERIALIZATION_GLM_HPP

#include <boost/serialization/nvp.hpp>

#include <neb/typedef.hpp>


namespace boost {
	namespace serialization {
		template<class Archive> void	serialize(Archive & ar, vec2 & a, const unsigned int version) {
			ar & boost::serialization::make_nvp("x",a.x);
			ar & boost::serialization::make_nvp("y",a.y);
		}
		template<class Archive> void	serialize(Archive & ar, vec3 & a, const unsigned int version) {
			ar & boost::serialization::make_nvp("x",a.x);
			ar & boost::serialization::make_nvp("y",a.y);
			ar & boost::serialization::make_nvp("z",a.z);
		}
		template<class Archive> void	serialize(Archive & ar, vec4 & a, const unsigned int version) {
			ar & boost::serialization::make_nvp("w",a.w);
			ar & boost::serialization::make_nvp("x",a.x);
			ar & boost::serialization::make_nvp("y",a.y);
			ar & boost::serialization::make_nvp("z",a.z);
		}
		template<class Archive> void	serialize(Archive & ar, quat & a, const unsigned int version) {
			ar & boost::serialization::make_nvp("w",a.w);
			ar & boost::serialization::make_nvp("x",a.x);
			ar & boost::serialization::make_nvp("y",a.y);
			ar & boost::serialization::make_nvp("z",a.z);
		}
		template<class Archive> void	serialize(Archive & ar, mat4 & a, const unsigned int version) {
			throw 0;
		}
	}
}

#endif

