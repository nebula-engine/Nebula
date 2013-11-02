#include <nebula/define.hpp>

#include <jess/free.hpp>
#include <jess/scoped_ostream.hpp>

#include <nebula/utilities/free.hpp>
#include <nebula/content/actor/admin/controller.hpp>
#include <nebula/content/actor/physics/material.hpp>
#include <nebula/content/actor/control/controller/base.hpp>

#include <nebula/content/actor/physics/controller.hpp>

n34200::controller::controller( std::shared_ptr<n34100::base> parent ):
	base( parent )
{
	jess::scoped_ostream( &jess::clog, NEB_FUNCSIG );
}
n34200::controller::~controller()
{
	jess::scoped_ostream( &jess::cout, NEB_FUNCSIG );
}
void	n34200::controller::init()
{
	jess::scoped_ostream( &jess::clog, NEB_FUNCSIG );

	n34200::base::init();
}
void	n34200::controller::shutdown()
{
	jess::scoped_ostream( &jess::clog, NEB_FUNCSIG );
}
void	n34200::controller::update()
{
	jess::scoped_ostream( &jess::cout, NEB_FUNCSIG );

}
void	n34200::controller::step( float dt )
{
	jess::scoped_ostream sos( &jess::clog, NEB_FUNCSIG );

	NEB_ASSERT( px_controller_ );
	NEB_ASSERT( !parent_.expired() );
	
	//update_move();
	
	jess::shared_ptr<n34100::controller::base> parent = std::dynamic_pointer_cast<n34100::controller::base>( parent_.lock() );

	NEB_ASSERT( parent->control_ );

	
	physx::PxVec3 move = parent->control_->move();

	// rotate
	physx::PxQuat yaw( parent->yaw_, physx::PxVec3(0,1,0) );

	move = yaw.rotate( move );

	
	
	// gravity for a flat world
	// accelerate
	/// \todo somehow calculate velocity somewhere by reading position form physx and approximating
	parent->velocity_.y -= 0.0f * dt;
	
	move += parent->velocity_;
	
	// move
	physx::PxVec3 disp = move * dt;
	physx::PxF32 minDist = 0.01;
	physx::PxF32 elapsedTime = dt;
	physx::PxControllerFilters filters = 0;
	physx::PxObstacleContext* obstacles = 0;

	//physx::PxU32 collisionFlags = 
	physx::PxU32 collision_flags = px_controller_->move( disp, minDist, elapsedTime, filters, obstacles );
	
	printf( "collision_flags = %i\n", collision_flags );
}


