#ifndef PHYSX_UTIL_CONVERT_HPP
#define PHYSX_UTIL_CONVERT_HPP

#include <glm/gtx/transform.hpp>

#include <PxPhysicsAPI.h>

#include <gal/math/pose.hpp>

namespace neb { namespace phx { namespace util {

	physx::PxVec2		convert(glm::vec2 const & v);
	physx::PxVec3		convert(glm::vec3 const & v);
	physx::PxVec4		convert(glm::vec4 const & v);
	physx::PxQuat		convert(glm::quat const & v);
	physx::PxMat44		convert(glm::mat4 const & v);
	glm::vec2		convert(physx::PxVec2 const & v);
	glm::vec3		convert(physx::PxVec3 const & v);
	glm::vec4		convert(physx::PxVec4 const & v);
	glm::quat		convert(physx::PxQuat const & v);
	glm::mat4		convert(physx::PxMat44 const & v);
	glm::mat4		convert(physx::PxTransform const & t);
	// pose
	physx::PxTransform	convert_pose(gal::math::pose const & pose);
	gal::math::pose	convert_pose(physx::PxTransform const & pose);
	

}}}

#endif
