#ifndef PHYSX_UTIL_CONVERT_HPP
#define PHYSX_UTIL_CONVERT_HPP

#include <glm/gtx/transform.hpp>

#include <PxPhysicsAPI.h>

#include <Nebula/Util/typedef.hpp>

namespace px { namespace util {


	physx::PxVec2		convert(vec2 const & v) {
		return physx::PxVec2(v.x, v.y);
	}
	physx::PxVec3		convert(vec3 const & v) {
		return physx::PxVec3(v.x, v.y, v.z);
	}
	physx::PxVec4		convert(vec4 const & v) {
		return physx::PxVec4(v.w, v.x, v.y, v.z);
	}
	physx::PxQuat		convert(quat const & v) {
		return physx::PxQuat(v.w, v.x, v.y, v.z);
	}


	vec2			convert(physx::PxVec2 const & v) {
		return vec2(v.x, v.y);
	}
	vec3			convert(physx::PxVec3 const & v) {
		return vec3(v.x, v.y, v.z);
	}
	vec4			convert(physx::PxVec4 const & v) {
		return vec4(v.w, v.x, v.y, v.z);
	}
	quat			convert(physx::PxQuat const & v) {
		return quat(v.w, v.x, v.y, v.z);
	}


	
	mat4			convert(physx::PxTransform const & t) {
		quat q(convert(t.q));
		vec3 p(convert(t.p));
		//mat4 ret(p,q);
		
		mat4 rot(glm::mat4_cast(q));
		mat4 tra(glm::translate(p));

		return rot * tra;
	}

}}

#endif
