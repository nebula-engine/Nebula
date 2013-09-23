#include <nebula/content/actor/admin/rigid_body.hpp>
#include <nebula/content/actor/physics/physx/material.hpp>
#include <nebula/content/actor/physics/physx/rigid_body.hpp>

#include <nebula/content/shape/admin/box.hpp>

#include <nebula/platform/renderer/base.hpp>







#include <nebula/content/shape/physics/physx/box.hpp>

namespace ncs = nebula::content::shape;
namespace nca = nebula::content::actor;


	ncs::physics::physx::box::Box()
{

}
	ncs::physics::physx::box::~Box()
{

}
void	ncs::physics::physx::box::VInit( Void* data )
{
	VCreatePxShape();
}
void	ncs::physics::physx::box::VShutDown()
{
	
}
void	ncs::physics::physx::box::VCreatePxShape()
{
	jess::clog.funcsig();
	
	nca::physics::physx::rigid_actor* acPhPxRigidActor = dynamic_cast<CO_AC_PH_PX_RigidActor*>(m_shAdShape->Get_CO_AC_AD_RigidActor()->Ptr<CO_AC_PH_RigidActor>::Get_Or_Error() );

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











