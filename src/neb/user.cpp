#include <glutpp/renderable.h>

#include <neb/user.h>
#include <neb/camera.h>
#include <neb/actor/Rigid_Body.h>

neb::user::user()
{}
void	neb::user::connect(std::shared_ptr<glutpp::window> w)
{
	printf("%s\n", __PRETTY_FUNCTION__);
	
	std::shared_ptr<neb::actor::Rigid_Body> actor =
			std::dynamic_pointer_cast<neb::actor::Rigid_Body>(actor_);
	
	assert(w);
	assert(actor);
	
	conn_.key_fun_ = w->sig_.key_fun_.connect(std::bind(
				&neb::actor::Rigid_Body::key_fun,
				actor,
				std::placeholders::_1,
				std::placeholders::_2,
				std::placeholders::_3,
				std::placeholders::_4));
	
	assert(conn_.key_fun_);
	
	
	
	
	
	assert(camera_control_);
	
	w->renderable_->camera_->control_ = camera_control_;

}
int	neb::user::set_actor(std::shared_ptr<neb::actor::Base> actor, neb::camera_type::e RIDEALONG)
{
	std::shared_ptr<neb::camera_ridealong> ride(new neb::camera_ridealong);
	
	actor_ = actor;
	camera_control_ = ride;

	ride->actor_ = actor_;

	return 0;
}

