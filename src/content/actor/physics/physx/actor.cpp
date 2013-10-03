#include <nebula/content/actor/physics/physx/actor.hpp>


nca::physics::physx::actor::actor()
{
}
nca::physics::physx::actor::~actor()
{
}
void	nca::physics::physx::actor::step(FLOAT dt)
{
	
}
void	nca::physics::physx::actor::set_px_actor( ::physx::PxActor* actor )
{
	px_actor_ = actor;
	
	px_actor_->userData = this;
}







