#include <PxPhysicsAPI.hpp>

#include <nebula/content/actor/admin/controller.hpp>

#include <nebula/content/actor/physics/physx/controller.hpp>

namespace nca = nebula::content::actor;
namespace ncapp = nca::physics::physx;

void	ncapp::controller::step(FLOAT dt)
{
	boost::shared_ptr<nca::admin::controller> parent = boost::dynamic_pointer_cast<nca::admin::controller>( parent_.lock() );
	
	::physx::PxVec3 disp = Vec3f_PxVec3( parent_->get_move() );
	::physx::PxF32 minDist = 0.1;
	::physx::PxF32 elapsedTime = s->dt;
	::physx::PxControllerFilters filters = 0;
	::physx::PxObstacleContext* obstacles = 0;
	
	::physx::PxU32 collisionFlags = px_controller_->move( disp, minDist, elapsedTime, filters, obstacles );


}










