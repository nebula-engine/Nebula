#include <glutpp/renderable.h>
#include <glutpp/scene.h>

#include <neb/simulation_callback.h>
#include <neb/shape.h>
#include <neb/view.h>
#include <neb/scene.h>
#include <neb/actor/desc.h>
#include <neb/actor/Actor.h>

neb::actor::Actor::Actor():
	px_actor_(NULL)
{}
void	neb::actor::Actor::set_pose(math::transform pose)
{
	pose_ = pose;
}
int	neb::actor::Actor::fire()
{
	neb::actor::Base::fire();
	
	return 0;
}
void	neb::actor::Actor::step_remote(double)
{}
int	neb::actor::Actor::release()
{
	neb::actor::Base::release();
	
	//assert(!scene_.expired());
	
	assert(px_actor_);
	px_actor_->release();
	px_actor_ = NULL;
	
	return 0;
}


