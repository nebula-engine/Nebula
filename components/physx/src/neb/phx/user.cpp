
#include <neb/gfx/Context/Base.hh>

#include <neb/core/util/config.hpp>

#include <neb/phx/core/actor/control/rigidbody/base.hpp>
#include <neb/phx/user.hh>

neb::phx::user::user()
{}
void			neb::phx::user::connect(std::shared_ptr<neb::gfx::window::base> w) {
	printf("%s\n", __PRETTY_FUNCTION__);
	
	assert(control_);
	
	auto control = ::std::dynamic_pointer_cast<neb::phx::core::actor::control::rigidbody::base>(control_);
	
	assert(w);
	assert(control);
	
	//printf("actor ref count = %i\n", (int)actor.use_count());
	

	control->conn_.key_fun_ = w->sig_.key_fun_.connect(
			::std::bind(
				&neb::phx::core::actor::control::rigidbody::base::key_fun,
				control,
				::std::placeholders::_1,
				::std::placeholders::_2,
				::std::placeholders::_3,
				::std::placeholders::_4,
				::std::placeholders::_5)
			);

	//printf("actor ref count = %i\n", (int)actor.use_count());

	//assert(control->conn_.key_fun_);
}
void			neb::phx::user::set_control(std::shared_ptr<neb::phx::core::actor::control::rigidbody::base> control) {
	//NEBULA_DEBUG_0_FUNCTION;

	control_ = control;
}





