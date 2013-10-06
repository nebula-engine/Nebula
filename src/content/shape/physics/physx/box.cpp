#include <nebula/define.hpp>

#include <PxPhysicsAPI.h>

#include <jess/free.hpp>
#include <jess/ostream.hpp>

#include <nebula/content/actor/admin/rigid_body.hpp>
#include <nebula/content/actor/admin/material.hpp>
#include <nebula/content/actor/physics/physx/material.hpp>
#include <nebula/content/actor/physics/physx/rigid_body.hpp>
#include <nebula/content/shape/admin/box.hpp>

#include <nebula/platform/renderer/base.hpp>

#include <nebula/content/shape/physics/physx/box.hpp>

#include <nebula/ns.hpp>

	ncs::physics::physx::box::box()
{

}
	ncs::physics::physx::box::~box()
{

}
void	ncs::physics::physx::box::init(const jess::shared_ptr<ncs::admin::box>&)
{
	create_shape();
}
void	ncs::physics::physx::box::shutdown()
{
	
}
void	ncs::physics::physx::box::create_shape()
{
	jess::clog << NEB_FUNCSIG << std::endl;
	
	// admin rigid_actor
	jess::shared_ptr<nca::admin::rigid_actor> ad_act = parent_.lock()->parent_.lock();

	// physics rigid_actor
	jess::shared_ptr<ncap::rigid_actor> ph_act = std::dynamic_pointer_cast<ncap::rigid_actor>( ad_act->physics_ );
	
	// physx rigid_actor
	jess::shared_ptr<ncapp::rigid_actor> ph_px_act = std::dynamic_pointer_cast<nca::physics::physx::rigid_actor>( ph_act );
	
	// Pxrigid_actor
	::physx::PxRigidActor* px_rigid_actor = (::physx::PxRigidActor*)( ph_px_act->px_actor_ );
	
	// physx material
	jess::shared_ptr<ncapp::material> mat = std::dynamic_pointer_cast<ncapp::material>( ad_act->materials_.at(0)->physics_ );
	//jess::assertion( bool(mat) ); //throw jess::except("no material");
	
	// PxMaterial
	::physx::PxMaterial* px_mat = mat->px_material_;
	jess::assertion( bool(px_mat) ); //throw jess::except("no material");
	
	// PxBoxGeometry
	::physx::PxBoxGeometry px_geometry( 1, 1, 1 );
	
	// PxShape
	px_shape_ = px_rigid_actor->createShape( px_geometry, *px_mat );
	jess::assertion( bool(px_shape_) );  //throw jess::except("m_pxShape");
}





