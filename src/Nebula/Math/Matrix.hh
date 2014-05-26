#ifndef NEBULA_MATH_MATRIX_HPP
#define NEBULA_MATH_MATRIX_HPP

#include <PxPhysicsAPI.h>

physx::PxMat44		lookat(physx::PxVec3 eye, physx::PxVec3 center, physx::PxVec3 up);
physx::PxMat44		SetPerspective(float left, float right, float bottom, float top, float n, float f);
physx::PxMat44		SetPerspective(float fovy, float aspect, float n, float f);
void			SetReflection(physx::PxPlane const & p);



#endif

