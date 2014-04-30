#ifndef NEBULA_MATH_MATRIX_HPP
#define NEBULA_MATH_MATRIX_HPP

#include <PxPhysicsAPI.h>

physx::PxMat44		lookat(physx::PxVec3 eye, physx::PxVec3 center, physx::PxVec3 up) {
	physx::PxVec3 F = center - eye;
	physx::PxVec3 f = F.getNormalized();

	physx::PxVec3 UP = up.getNormalized();

	physx::PxVec3 s = f.cross(UP);
	s.normalize();

	physx::PxVec3 u = s.cross(f);

	//printf("u\n");
	//u.print();

	physx::PxMat44 M(s,u,-f,physx::PxVec3(0));


	//	M.print();

	physx::PxMat44 t(physx::PxTransform(-eye));
	//t.SetTranslation(-eye);

	//printf("M\n");
	//M.print();
	//printf("T\n");
	//T.print();
	
	//return T*M;
	return M * t;
}

physx::PxMat44		SetPerspective(float left, float right, float bottom, float top, float n, float f) {
	float nudge=0.999f;		//prevent artifacts with infinite far plane

	physx::PxMat44 ret;

	//matbase<float,4,4>::loadZero();

	//check for division by 0
	if(left==right || top==bottom || n==f)
	{
		printf("invalid perspective");
		exit(0);
	}

	ret(0,0) = (2*n)/(right-left);

	ret(1,1) = (2*n)/(top-bottom);

	ret(2,0) = (right+left)/(right-left);
	ret(2,1) = (top+bottom)/(top-bottom);

	if(f!=-1)
	{
		ret(2,2) = -(f+n)/(f-n);
	}
	else		//if f==-1, use an infinite far plane
	{
		ret(2,2) = -nudge;
	}

	ret(2,3) = -1;

	if(f!=-1)
	{
		ret(3,2) = -(2*f*n)/(f-n);
	}
	else		//if f==-1, use an infinite far plane
	{
		ret(3,2) = -2*n*nudge;
	}

	return ret;
}



physx::PxMat44		SetPerspective(float fovy, float aspect, float n, float f)
{
	float left, right, top, bottom;

	//convert fov from degrees to radians
	fovy *= (float)M_PI / 180.0f;
	
	top = n*tanf(fovy/2.0f);
	bottom=-top;
	
	left=aspect*bottom;
	right=aspect*top;
	
	return SetPerspective(left, right, bottom, top, n, f);
}






void	SetReflection(physx::PxPlane const & p) {

	physx::PxVec3 n = p.n.getNormalized();

	physx::PxMat44 A(physx::PxTransform(n * -p.d));
	//vA.SetTranslation(n * -p.d);

	physx::PxMat44 I;

	physx::PxVec4 a(n,0);

	//physx::PxMat44 RA = I - (a * a) * 2.0;

	//*this = A * RA * A.GetInverse();
	//*this = A.GetInverse() * RA * A;
	//
	throw 0;
}



#endif

