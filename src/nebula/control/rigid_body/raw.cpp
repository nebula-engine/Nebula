#include <neb/control/rigid_body/control.h>
#include <neb/control/rigid_body/raw.h>


neb::control::rigid_body::raw::raw():
	q_target_(math::quat(0.0 * M_PI,math::vec3(1.0,0.0,0.0)))
{
	
}
void neb::control::rigid_body::raw::load(neb::control::rigid_body::control_s control) {
	
	*this = control->raw_;
}



