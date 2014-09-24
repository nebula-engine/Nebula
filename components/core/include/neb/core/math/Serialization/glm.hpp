#ifndef NEBULA_SERIALIZATION_GLM_HPP
#define NEBULA_SERIALIZATION_GLM_HPP

#include <boost/serialization/nvp.hpp>

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

namespace boost {
	namespace serialization {
		template<class Archive> void	serialize(Archive & ar, glm::vec2 & a, const unsigned int & version) {
			ar & boost::serialization::make_nvp("x",a.x);
			ar & boost::serialization::make_nvp("y",a.y);
		}
		template<class Archive> void	serialize(Archive & ar, glm::vec3 & a, const unsigned int & version) {
			ar & boost::serialization::make_nvp("x",a.x);
			ar & boost::serialization::make_nvp("y",a.y);
			ar & boost::serialization::make_nvp("z",a.z);
		}
		template<class Archive> void	serialize(Archive & ar, glm::vec4 & a, const unsigned int & version) {
			ar & boost::serialization::make_nvp("w",a.w);
			ar & boost::serialization::make_nvp("x",a.x);
			ar & boost::serialization::make_nvp("y",a.y);
			ar & boost::serialization::make_nvp("z",a.z);
		}
		template<class Archive> void	serialize(Archive & ar, glm::quat & a, const unsigned int & version) {
			ar & boost::serialization::make_nvp("w",a.w);
			ar & boost::serialization::make_nvp("x",a.x);
			ar & boost::serialization::make_nvp("y",a.y);
			ar & boost::serialization::make_nvp("z",a.z);
		}
		template<class Archive> void	serialize(Archive & ar, glm::mat4 & a, const unsigned int & version) {
			throw 0;
		}
	}
}

#endif

