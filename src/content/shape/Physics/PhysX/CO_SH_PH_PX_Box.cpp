#include <PxPhysicsAPI.h>

#include <jess/ostream.hpp>

#include <nebula/content/actor/admin/rigid_body.hpp>
#include <nebula/content/actor/physics/physx/material.hpp>
#include <nebula/content/actor/physics/physx/rigid_body.hpp>

#include <nebula/content/shape/admin/box.hpp>

#include <nebula/platform/renderer/base.hpp>





#include <nebula/content/shape/physics/physx/box.hpp>

namespace ncs = nebula::content::shape;
namespace nca = nebula::content::actor;


	ncs::physics::physx::box::box()
{

}
	ncs::physics::physx::box::~box()
{

}
void	ncs::physics::physx::box::init(const boost::shared_ptr<ncs::admin::box>&)
{
	create_shape();
}
void	ncs::physics::physx::box::shutdown()
{
	
}
void	ncs::physics::physx::box::create_shape()
{
	jess::clog.funcsig();
	
	// admin rigid_actor
	boost::shared_ptr<nca::admin::rigid_actor> ad_act = parent_.lock()->parent_.lock();
	
	// physx rigid_actor
	boost::shared_ptr<nca::physics::physx::rigid_actor> ph_act = boost::dynamic_pointer_cast<nca::physics::physx::rigid_actor>(ad_act->physics_.pointer_);
	
	// px rigid_actor
	::physx::PxRigidActor* pxRigidActor = (::physx::PxRigidActor*)ph_act->px_actor_;//(physx::PxRigidActor*)m_rigidActor->GetPxActor();
	
	
	
	//physx::PxMaterial* pxMaterial = acPhPxRigidActor->GetPxMaterial(0);
	boost::shared_ptr<nca::physics::physx::material> mat = boost::dynamic_pointer_cast<nca::physics::physx::material>( ph_act->materials_->at(0) );
	if ( !material ) throw jess::except("no material");

	physx::PxMaterial* pxMaterial = material->m_pxMaterial;
	if ( !pxMaterial ) throw jess::except("no material");
	
	physx::PxBoxGeometry pxGeometry( 1, 1, 1 );
	
	m_pxShape = pxRigidActor->createShape( pxGeometry, *pxMaterial );
	jess::assertion( m_pxShape );  //throw jess::except("m_pxShape");
}











