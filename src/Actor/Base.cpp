#include <NEB/Actor/Base.h>

NEB::Actor::Base::Base():
	pose_( physx::PxTransform( physx::PxVec3(0.0f, 0.0f, 0.0f), physx::PxQuat( 0.0f, physx::PxVec3(1.0f, 0.0f, 0.0f) ) ) )
{

}
