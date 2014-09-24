#ifndef NEBULA_SERIALIZATION_GLM_HPP
#define NEBULA_SERIALIZATION_GLM_HPP

#include <boost/serialization/nvp.hpp>

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

namespace boost {
	namespace serialization {
<<<<<<< HEAD
		template<class Archive> void	serialize(Archive & ar, glm::vec2 & a, const unsigned int version) {
			ar & boost::serialization::make_nvp("x",a.x);
			ar & boost::serialization::make_nvp("y",a.y);
		}
		template<class Archive> void	serialize(Archive & ar, glm::vec3 & a, const unsigned int version) {
=======
		template<class Archive> void	serialize(Archive & ar, glm::vec2 & a, const unsigned int & version) {
			ar & boost::serialization::make_nvp("x",a.x);
			ar & boost::serialization::make_nvp("y",a.y);
		}
		template<class Archive> void	serialize(Archive & ar, glm::vec3 & a, const unsigned int & version) {
>>>>>>> d0f62233eb8fed722542d3bfcc237575d904a507
			ar & boost::serialization::make_nvp("x",a.x);
			ar & boost::serialization::make_nvp("y",a.y);
			ar & boost::serialization::make_nvp("z",a.z);
		}
<<<<<<< HEAD
		template<class Archive> void	serialize(Archive & ar, glm::vec4 & a, const unsigned int version) {
=======
		template<class Archive> void	serialize(Archive & ar, glm::vec4 & a, const unsigned int & version) {
>>>>>>> d0f62233eb8fed722542d3bfcc237575d904a507
			ar & boost::serialization::make_nvp("w",a.w);
			ar & boost::serialization::make_nvp("x",a.x);
			ar & boost::serialization::make_nvp("y",a.y);
			ar & boost::serialization::make_nvp("z",a.z);
		}
<<<<<<< HEAD
		template<class Archive> void	serialize(Archive & ar, glm::quat & a, const unsigned int version) {
=======
		template<class Archive> void	serialize(Archive & ar, glm::quat & a, const unsigned int & version) {
>>>>>>> d0f62233eb8fed722542d3bfcc237575d904a507
			ar & boost::serialization::make_nvp("w",a.w);
			ar & boost::serialization::make_nvp("x",a.x);
			ar & boost::serialization::make_nvp("y",a.y);
			ar & boost::serialization::make_nvp("z",a.z);
		}
<<<<<<< HEAD
		template<class Archive> void	serialize(Archive & ar, glm::mat4 & a, const unsigned int version) {
=======
		template<class Archive> void	serialize(Archive & ar, glm::mat4 & a, const unsigned int & version) {
>>>>>>> d0f62233eb8fed722542d3bfcc237575d904a507
			throw 0;
		}
	}
}

#endif

