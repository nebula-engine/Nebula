#ifndef NEBULA_MATH_SERIALIZATION_HPP
#define NEBULA_MATH_SERIALIZATION_HPP

#include <boost/serialization/nvp.hpp>

#include <PxPhysicsAPI.h>

namespace boost {
	namespace serialization {
		template<class Archive> void	serialize(Archive & ar, physx::PxVec4 & a, const unsigned int version)
		{
			ar & boost::serialization::make_nvp("w",a.w);
			ar & boost::serialization::make_nvp("x",a.x);
			ar & boost::serialization::make_nvp("y",a.y);
			ar & boost::serialization::make_nvp("z",a.z);
		}
		template<class Archive> void	serialize(Archive & ar, physx::PxVec3 & a, const unsigned int version)
		{
			ar & boost::serialization::make_nvp("x",a.x);
			ar & boost::serialization::make_nvp("y",a.y);
			ar & boost::serialization::make_nvp("z",a.z);
		}
		template<class Archive> void	serialize(Archive & ar, physx::PxQuat & a, const unsigned int version)
		{
			ar & boost::serialization::make_nvp("w",a.w);
			ar & boost::serialization::make_nvp("x",a.x);
			ar & boost::serialization::make_nvp("y",a.y);
			ar & boost::serialization::make_nvp("z",a.z);
		}
		template<class Archive> void	serialize(Archive & ar, physx::PxTransform & a, const unsigned int version)
		{
			ar & boost::serialization::make_nvp("p",a.p);
			ar & boost::serialization::make_nvp("q",a.q);
		}
	}
}


#endif

