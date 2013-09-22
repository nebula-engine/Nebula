#include <content/Actor/Physics/PhysX/CO_AC_PH_PX_RigidBody.h>



void	Content::Actor::Physics::PhysX::RigidBody::VInit( Void* data ) {
	PRINTSIG;
	CO_AC_PH_PX_RigidActor::VInit( data );

	m_velocity = physx::PxVec3(0,1,0);
	m_density = 1000;

	if (!m_pxActor) 
	
	m_pxRigidBody = (physx::PxRigidBody*)m_pxActor;
	
	//VCreateShape();
	
	
	
	physx::PxRigidBodyExt::updateMassAndInertia( *m_pxRigidBody, m_density );
	
	m_pxRigidBody->setLinearVelocity( m_velocity );
	
}









