#include <content/Actor/Admin/CO_AC_AD_Controller.h>






#include <content/Actor/Physics/PhysX/CO_AC_PH_PX_Controller.h>


void	CO_AC_PH_PX_Controller::VStep( Void* v ) {
	AR_Step* s = DynCast<Void,AR_Step>(v);
	
	

	physx::PxVec3 disp = Vec3f_PxVec3( Ptr<CO_AC_AD_Controller>::Get_Or_Error()->GetMove() );
	physx::PxF32 minDist = 0.1;
	physx::PxF32 elapsedTime = s->dt;
	physx::PxControllerFilters filters = 0;
	physx::PxObstacleContext* obstacles = 0;
	
	physx::PxU32 collisionFlags = m_pxcontroller->move( disp, minDist, elapsedTime, filters, obstacles );


}










