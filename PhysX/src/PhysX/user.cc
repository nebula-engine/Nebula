
#include <Nebula/Graphics/Context/Base.hh>

#include <Nebula/config.hh>
#include <Nebula/user.hh>
//#include <nebula/camera/camera.hpp>
#include <Nebula/Actor/Control/RigidBody/Base.hh>

neb::User::User()
{}
void	neb::User::connect(sp::shared_ptr<neb::gfx::window::base> w) {
	printf("%s\n", __PRETTY_FUNCTION__);
	
	assert(control_);
	
	auto control = std::dynamic_pointer_cast<neb::core::actor::Control::RigidBody::base>(control_);
	
	assert(w);
	assert(control);
	
	//printf("actor ref count = %i\n", (int)actor.use_count());
	
	
	control->conn_.key_fun_ = w->sig_.key_fun_.connect(std::bind(
				&neb::core::actor::Control::RigidBody::base::key_fun,
				control,
				std::placeholders::_1,
				std::placeholders::_2,
				std::placeholders::_3,
				std::placeholders::_4));
	
	//printf("actor ref count = %i\n", (int)actor.use_count());

	//assert(control->conn_.key_fun_);
}
void neb::User::set_control(sp::shared_ptr<neb::core::actor::Control::RigidBody::base> control) {
	//NEBULA_DEBUG_0_FUNCTION;

	control_ = control;
}





