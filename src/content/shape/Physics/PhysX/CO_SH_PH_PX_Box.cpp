#include <content/Actor/Admin/CO_AC_AD_RigidBody.h>
#include <content/Actor/Physics/PhysX/CO_AC_PH_PX_Material.h>
#include <content/Actor/Physics/PhysX/CO_AC_PH_PX_RigidBody.h>

#include <content/Shape/Admin/CO_SH_AD_Box.h>

#include <Platform/Renderer/PL_RE_Renderer.h>











#include <content/Shape/Physics/PhysX/CO_SH_PH_PX_Box.h>

		CO_SH_PH_PX_Box::Box() {
}
		CO_SH_PH_PX_Box::~Box() {
}
	
void	CO_SH_PH_PX_Box::VInit( Void* data ) {
	VCreatePxShape();
}
void	CO_SH_PH_PX_Box::VShutDown() {
	
}
void	CO_SH_PH_PX_Box::VCreatePxShape() {
	PRINTSIG;
	
	CO_AC_PH_PX_RigidActor* acPhPxRigidActor = dynamic_cast<CO_AC_PH_PX_RigidActor*>(m_shAdShape->Get_CO_AC_AD_RigidActor()->Ptr<CO_AC_PH_RigidActor>::Get_Or_Error() );

	physx::PxRigidActor* pxRigidActor = (physx::PxRigidActor*)acPhPxRigidActor->GetPxActor();//(physx::PxRigidActor*)m_rigidActor->GetPxActor();
	


	//physx::PxMaterial* pxMaterial = acPhPxRigidActor->GetPxMaterial(0);

	CO_AC_PH_PX_Material* material = (CO_AC_PH_PX_Material*)acPhPxRigidActor->GetMaterial(0);
	if ( !material ) throw Except("no material");

	physx::PxMaterial* pxMaterial = material->m_pxMaterial;
	if ( !pxMaterial ) throw Except("no material");
	
	physx::PxBoxGeometry pxGeometry( 1, 1, 1 );
	
	m_pxShape = pxRigidActor->createShape( pxGeometry, *pxMaterial );
	if (!m_pxShape) throw Except("m_pxShape");
}











