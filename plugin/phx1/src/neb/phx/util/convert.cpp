
#include <glm/gtx/transform.hpp>
#include <glm/gtx/quaternion.hpp>

#include <PxPhysicsAPI.h>

#include <neb/phx/util/convert.hpp>

physx::PxVec2		neb::phx::util::convert(glm::vec2 const & v)
{
	return physx::PxVec2(v.x, v.y);
}
physx::PxVec3		neb::phx::util::convert(glm::vec3 const & v) {
	return physx::PxVec3(v.x, v.y, v.z);
}
physx::PxVec4		neb::phx::util::convert(glm::vec4 const & v) {
	return physx::PxVec4(v.w, v.x, v.y, v.z);
}
physx::PxQuat		neb::phx::util::convert(glm::quat const & v)
{
	return physx::PxQuat(v.w, v.x, v.y, v.z);
}

physx::PxMat44		neb::phx::util::convert(glm::mat4 const & v) {
	return physx::PxMat44((float*)&v[0]);
}


glm::vec2			neb::phx::util::convert(physx::PxVec2 const & v)
{
	return glm::vec2(v.x, v.y);
}
glm::vec3			neb::phx::util::convert(physx::PxVec3 const & v)
{
	return glm::vec3(v.x, v.y, v.z);
}
glm::vec4			neb::phx::util::convert(physx::PxVec4 const & v)
{
	return glm::vec4(v.w, v.x, v.y, v.z);
}
glm::quat			neb::phx::util::convert(physx::PxQuat const & v)
{
	return glm::quat(v.w, v.x, v.y, v.z);
}
glm::mat4			neb::phx::util::convert(physx::PxMat44 const & v)
{
	return glm::mat4(
			v[0][0],
			v[0][1],
			v[0][2],
			v[0][3],
			v[1][0],
			v[1][1],
			v[1][2],
			v[1][3],
			v[2][0],
			v[2][1],
			v[2][2],
			v[2][3],
			v[3][0],
			v[3][1],
			v[3][2],
			v[3][3]
		   );
}
glm::mat4			neb::phx::util::convert(physx::PxTransform const & t)
{
	glm::quat q(convert(t.q));
	glm::vec3 p(convert(t.p));
	//mat4 ret(p,q);

	glm::mat4 rot(glm::mat4_cast(q));
	glm::mat4 tra(glm::translate(p));

	return rot * tra;
}
physx::PxTransform	neb::phx::util::convert_pose(gal::math::pose const & pose)
{
	return physx::PxTransform(
			convert(pose.pos_),
			convert(pose.rot_));
}
gal::math::pose	neb::phx::util::convert_pose(physx::PxTransform const & pose)
{
	return gal::math::pose(
			convert(pose.p),
			convert(pose.q));
}




