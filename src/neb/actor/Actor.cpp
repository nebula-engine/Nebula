#include <glutpp/renderable.h>
#include <glutpp/scene/scene.h>

#include <neb/simulation_callback.h>
#include <neb/shape.h>
#include <neb/scene/scene.h>
#include <glutpp/actor/desc.h>
#include <neb/actor/Actor.h>

neb::actor::Actor::Actor(
		glutpp::actor::desc_shared desc,
		std::shared_ptr<neb::scene::scene> scene,
		std::shared_ptr<neb::actor::Base> actor):
	neb::actor::Base(desc, scene, actor),
	px_actor_(NULL)
{}
void neb::actor::Actor::init() {
	
	neb::actor::Base::init();
}
void	neb::actor::Actor::set_pose(math::transform pose)
{
	neb::actor::Base::set_pose(pose);
}
int	neb::actor::Actor::fire()
{
	neb::actor::Base::fire();

	return 0;
}
void neb::actor::Actor::step_remote(double)
{
	abort();
}
void neb::actor::Actor::release()
{
	neb::actor::Base::release();

	//assert(!scene_.expired());

	assert(px_actor_);
	px_actor_->release();
	px_actor_ = NULL;
}
glutpp::actor::desc_shared neb::actor::Actor::get_desc() {

	return neb::actor::Base::get_desc();
}
glutpp::actor::desc_shared get_projectile() {
	abort();
	return glutpp::actor::desc_shared();
}




