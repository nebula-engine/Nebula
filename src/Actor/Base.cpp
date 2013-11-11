#include <NEB/Actor/Base.h>

NEB::Actor::Base::Base():
	pose_( physx::PxTransform( physx::PxVec3(0,0,0), physx::PxQuat( 0, physx::PxVec3(1,0,0) ) ) )
{

}
