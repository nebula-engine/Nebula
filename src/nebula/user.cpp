#include <glutpp/renderable.h>

#include <neb/config.h>
#include <neb/user.h>
#include <neb/camera/camera.h>
#include <neb/control/rigid_body/control.h>

neb::user::user()
{}
void	neb::user::connect(glutpp::window::window_s w)
{
	printf("%s\n", __PRETTY_FUNCTION__);
	
	assert(control_);
	
	auto control = std::dynamic_pointer_cast<neb::control::rigid_body::control>(control_);
	
	assert(w);
	assert(control);
	
	//printf("actor ref count = %i\n", (int)actor.use_count());
	
	
	control->conn_.key_fun_ = w->sig_.key_fun_.connect(std::bind(
				&neb::control::rigid_body::control::key_fun,
				control,
				std::placeholders::_1,
				std::placeholders::_2,
				std::placeholders::_3,
				std::placeholders::_4));
	
	//printf("actor ref count = %i\n", (int)actor.use_count());

	assert(control->conn_.key_fun_);
}
void neb::user::set_control(neb::control::rigid_body::control_s control) {
	NEBULA_DEBUG_0_FUNCTION;

	control_ = control;
}





