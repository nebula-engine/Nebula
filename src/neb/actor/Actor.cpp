#include <glutpp/renderable.h>
#include <glutpp/scene.h>

#include <neb/shape.h>
#include <neb/view.h>
#include <neb/scene.h>
#include <neb/actor/desc.h>
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
int	neb::actor::Actor::fire(int,int,int)
{
	neb::actor::desc desc(neb::actor::RIGID_DYNAMIC);
	
	desc.pose_ = pose_;
	desc.pose_.p += math::vec3(0.0, 0.0, -2.0);
	
	
	neb::shape* shape = new neb::box(math::vec3(0.1,0.1,0.1));
	
	desc.shape_ = shape;
	
	assert(!scene_.expired());
	
	std::shared_ptr<neb::actor::Rigid_Dynamic> actor = scene_.lock()->Create_Rigid_Dynamic(desc);
	
	
	
	scene_.lock()->view_.lock()->window_.lock()->renderable_->scene_->add_object(actor->object_);
	
	return 1;
}
void	neb::actor::Base::step_remote(double)
{}

