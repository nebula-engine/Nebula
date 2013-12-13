#include <neb/actor/Actor.h>

neb::actor::Actor::Actor():
	px_actor_(NULL),
	object_(NULL)
{}
void	neb::actor::Actor::set_pose(math::transform pose)
{
	pose_ = pose;

	object_->pose_ = pose;
}


