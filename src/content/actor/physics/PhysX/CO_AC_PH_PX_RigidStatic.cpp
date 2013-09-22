#include <content/Actor/Physics/PhysX/CO_AC_PH_PX_RigidStatic.h>



void	CO_AC_PH_PX_RigidStatic::VInit( Void* data ) {
	PRINTSIG;
	CO_AC_PH_PX_RigidActor::VInit( data );
	
	if (!m_pxActor) 
	
	m_pxRigidStatic = (physx::PxRigidStatic*)m_pxActor;
	
	//VCreateShape();
}






