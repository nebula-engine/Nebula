#ifndef PHYSX_UTIL_CONVERT_HPP
#define PHYSX_UTIL_CONVERT_HPP

#include <glm/gtx/transform.hpp>

#include <PxPhysicsAPI.h>

#include <Nebula/Util/typedef.hpp>

namespace phx { namespace util {


	physx::PxVec2		convert(vec2 const & v);
	physx::PxVec3		convert(vec3 const & v);
	physx::PxVec4		convert(vec4 const & v);
	physx::PxQuat		convert(quat const & v);
	physx::PxMat44		convert(mat4 const & v);
	vec2			convert(physx::PxVec2 const & v);
	vec3			convert(physx::PxVec3 const & v);
	vec4			convert(physx::PxVec4 const & v);
	quat			convert(physx::PxQuat const & v);
	mat4			convert(physx::PxMat44 const & v);
	mat4			convert(physx::PxTransform const & t);

}}

#endif
