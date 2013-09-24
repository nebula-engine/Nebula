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

namespace ncs = nebula::content::shape;
namespace nca = nebula::content::actor;
namespace ncapp = nca::physics::physx;

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

	boost::shared_ptr<nca::physics::rigid_actor> ph_act = ad_act->physics_.pointer_;
	
	// physx rigid_actor
	boost::shared_ptr<ncapp::rigid_actor> ph_px_act = boost::dynamic_pointer_cast<nca::physics::physx::rigid_actor>( ph_act );
	
	// PxRigidActor
	boost::shared_ptr< ::physx::PxRigidActor> px_rigid_actor = boost::dynamic_pointer_cast< ::physx::PxRigidActor>( ph_px_act->px_actor_ );
	
	// physx material
	boost::shared_ptr<ncapp::material> mat = boost::dynamic_pointer_cast<ncapp::material>( ad_act->materials_.at(0)->physics_.pointer_ );
	jess::assertion( bool(mat) ); //throw jess::except("no material");
	
	// PxMaterial
	boost::shared_ptr< ::physx::PxMaterial> px_mat = mat->px_material_;
	jess::assertion( bool(px_mat) ); //throw jess::except("no material");
	
	// PxBoxGeometry
	::physx::PxBoxGeometry px_geometry( 1, 1, 1 );
	
	// PxShape
	px_shape_ = px_rigid_actor->createShape( px_geometry, *px_mat );
	jess::assertion( bool(px_shape_) );  //throw jess::except("m_pxShape");
}





