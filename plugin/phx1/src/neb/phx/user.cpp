
//#include <neb/gfx/Context/Base.hh>

#include <neb/fnd/util/config.hpp>

#include <neb/phx/core/actor/control/rigidbody/base.hpp>
#include <neb/phx/user.hpp>

neb::phx::user::user()
{}
void			neb::phx::user::connect(std::shared_ptr<neb::fnd::input::source> src)
{

/*
	printf("%s\n", __PRETTY_FUNCTION__);
	
	assert(control_);
	
	auto control = ::std::dynamic_pointer_cast<neb::phx::core::actor::control::rigidbody::base>(control_);
	
	assert(w);
	assert(control);
	
	//printf("actor ref count = %i\n", (int)actor.use_count());
	
	connectKeyFun(src, 10);
	
	//printf("actor ref count = %i\n", (int)actor.use_count());

	//assert(control->conn_.key_fun_);
	//
	*/
}
void			neb::phx::user::set_control(std::shared_ptr<neb::fnd::core::actor::control::rigidbody::base> control) {
	//NEBULA_DEBUG_0_FUNCTION;

	control_ = control;
}





