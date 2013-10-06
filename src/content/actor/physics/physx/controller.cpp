#include <nebula/define.hpp>

#include <PxPhysicsAPI.h>

#include <nebula/content/physics/physx/free.hpp>
#include <nebula/content/actor/admin/controller.hpp>
#include <nebula/content/actor/physics/physx/controller.hpp>

#include <nebula/ns.hpp>

void	ncapp::controller::step(FLOAT dt)
{
	jess::shared_ptr<nca::admin::controller> parent = boost::dynamic_pointer_cast<nca::admin::controller>( parent_.lock() );
	
	::physx::PxVec3 disp = ncpp::boost_to_physx( parent->get_move() );
	::physx::PxF32 minDist = 0.1;
	::physx::PxF32 elapsedTime = dt;
	::physx::PxControllerFilters filters = 0;
	::physx::PxObstacleContext* obstacles = 0;
	
	//::physx::PxU32 collisionFlags = 
	px_controller_->move( disp, minDist, elapsedTime, filters, obstacles );
	

}










