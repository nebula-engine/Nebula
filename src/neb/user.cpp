#include <glutpp/renderable.h>

#include <neb/user.h>
#include <neb/camera.h>
#include <neb/actor/Rigid_Body.h>

neb::user::user()
{}
void	neb::user::connect(glutpp::window::window_s w)
{
	printf("%s\n", __PRETTY_FUNCTION__);

	assert(!actor_.expired());
	
	auto actor = std::dynamic_pointer_cast<neb::actor::Rigid_Body>(actor_.lock());
	
	assert(w);
	assert(actor);

	//printf("actor ref count = %i\n", (int)actor.use_count());
	
	
	actor->conn_.key_fun_ = w->sig_.key_fun_.connect(std::bind(
				&neb::actor::Rigid_Body::key_fun,
				actor,
				std::placeholders::_1,
				std::placeholders::_2,
				std::placeholders::_3,
				std::placeholders::_4));
	
	//printf("actor ref count = %i\n", (int)actor.use_count());

	
	assert(actor->conn_.key_fun_);
	
	assert(camera_control_);
	
	w->renderable_->camera_->control_ = camera_control_;

}
int	neb::user::set_actor(std::shared_ptr<neb::actor::Base> actor, neb::camera_type::e RIDEALONG)
{
	NEBULA_DEBUG_0_FUNCTION;

	std::shared_ptr<neb::camera_ridealong> ride(new neb::camera_ridealong);

	//printf("actor ref count = %i\n", (int)actor.use_count());
	
	actor_ = actor;
	camera_control_ = ride;

	//printf("actor ref count = %i\n", (int)actor.use_count());

	ride->actor_ = actor_;

	printf("actor ref count = %i\n", (int)actor.use_count());
	
	return 0;
}

