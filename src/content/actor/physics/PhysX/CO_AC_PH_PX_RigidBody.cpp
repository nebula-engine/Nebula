#include <PxPhysicsAPI.h>

#include <jess/free.hpp>

#include <nebula/content/physics/physx/free.hpp>

#include <nebula/content/actor/physics/physx/rigid_body.hpp>



void	ncapp::rigid_body::init(const boost::shared_ptr<ncaa::base>& parent)
{
	ncapp::rigid_actor::init(parent);
	
	velocity_ = bnu::vector<FLOAT>(3);//::physx::PxVec3(0,1,0);
	velocity_(0) = 0;
	velocity_(1) = 0;
	velocity_(2) = 0;
	
	density_ = 1000;
	
	jess::assertion( px_actor_ );
	
	::physx::Pxrigid_body* px_rigid_body = (::physx::Pxrigid_body*)px_actor_;
	
	//VCreateShape();
	
	
	
	::physx::Pxrigid_bodyExt::updateMassAndInertia( *px_rigid_body, density_ );
	
	px_rigid_body->setLinearVelocity( ncpp::boost_to_physx(velocity_) );
	
}









