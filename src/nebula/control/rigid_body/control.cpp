#include <math/mat33.hpp>

#include <nebula/control/rigid_body/control.hpp>

neb::control::rigid_body::control::control() {

}
int neb::control::rigid_body::control::key_fun(int key, int scancode, int action, int mods) {
	NEBULA_DEBUG_0_FUNCTION;

	math::vec3<double> x(1.0,0.0,0.0);
	math::vec3<double> y(0.0,1.0,0.0);
	math::vec3<double> z(0.0,0.0,1.0);

	switch(action)
	{
		case GLFW_PRESS:
			switch(key)
			{
				case GLFW_KEY_D:
					raw_.f_ += x;
					return 1;
				case GLFW_KEY_A:
					raw_.f_ -= x;
					return 1;
				case GLFW_KEY_E:
					raw_.f_ += y;
					return 1;
				case GLFW_KEY_Q:
					raw_.f_ -= y;
					return 1;
				case GLFW_KEY_W:
					raw_.f_ -= z;
					return 1;
				case GLFW_KEY_S:
					raw_.f_ += z;
					return 1;
				case GLFW_KEY_I:
					raw_.t_ += x;
					return 1;
				case GLFW_KEY_K:
					raw_.t_ -= x;
					return 1;
				case GLFW_KEY_L:
					raw_.t_ -= y;
					return 1;
				case GLFW_KEY_J:
					raw_.t_ += y;
					return 1;
				case GLFW_KEY_O:
					raw_.t_ -= z;
					return 1;
				case GLFW_KEY_U:
					raw_.t_ += z;
					return 1;
				default:
					return 0;
			}
		case GLFW_RELEASE:
			switch(key)
			{
				case GLFW_KEY_D:
					raw_.f_ -= x;
					return 1;
				case GLFW_KEY_A:
					raw_.f_ += x;
					return 1;
				case GLFW_KEY_E:
					raw_.f_ -= y;
					return 1;
				case GLFW_KEY_Q:
					raw_.f_ += y;
					return 1;
				case GLFW_KEY_W:
					raw_.f_ += z;
					return 1;
				case GLFW_KEY_S:
					raw_.f_ -= z;
					return 1;
				case GLFW_KEY_I:
					raw_.t_ -= x;
					return 1;
				case GLFW_KEY_K:
					raw_.t_ += x;
					return 1;
				case GLFW_KEY_L:
					raw_.t_ += y;
					return 1;
				case GLFW_KEY_J:
					raw_.t_ -= y;
					return 1;
				case GLFW_KEY_O:
					raw_.t_ += z;
					return 1;
				case GLFW_KEY_U:
					raw_.t_ -= z;
					return 1;
				default:
					return 0;
			}
	}


	return 0;
}
void neb::control::rigid_body::control::step_local(double time) {
	NEBULA_DEBUG_1_FUNCTION;
	
	switch(raw_.type_) {
		case neb::control::rigid_body::type::T0:
			return step_local0(time);
		case neb::control::rigid_body::type::T1:
			return step_local1(time);
		default:
			break;
	}
}
void neb::control::rigid_body::control::step_local0(double time) {
	
}
void neb::control::rigid_body::control::step_local1(double time) {
	NEBULA_DEBUG_1_FUNCTION;
	
	double dt = time - last_; last_ = time;
	
	// step target
	
	float q_scale = 0.5;
	float p_scale = 0.5;
	
	if(raw_.t_.magnitude() == 0.0f)
	{
		//printf("no key\n");
	}
	else
	{
		math::quat rot(q_scale * dt, raw_.t_);

		raw_.q_target_ *= rot;

		printf("q_target_=\n");
		raw_.q_target_.print();


		raw_.p_target_ += raw_.f_ * p_scale;


		//printf("p_target_=\n");
		//p_target_.print();
	}

	// get actor
	assert(!actor_.expired());
	auto actor = std::dynamic_pointer_cast<neb::Actor::Actor>(actor_.lock());
	auto pxrigidbody = actor->px_actor_->isRigidBody();


	// rotation from pose to target pose
	math::quat q = actor->get_raw()->pose_.q;
	math::quat a = raw_.q_target_.getConjugate() * q;




	// angular velocity
	math::vec3<double> omega = pxrigidbody->getAngularVelocity();
	omega = q.rotate(omega);
	
	// inertia matrix
	math::vec3<double> vI = pxrigidbody->getMassSpaceInertiaTensor();
	math::mat33 I(vI);
	




	
/*
	math::mat33 ac(
			0, -a.z, a.y,
			a.z, 0, -a.x,
			-a.y, a.x, 0);
*/
	
	//math::mat33 Gp(math::vec3(750, 800, 400));
	//math::mat33 Gr(math::vec3(600, 550, 250));

/*
	float x = 10;
	float y = 100;
	math::mat33 Gp(math::vec3(x,x,x));
	math::mat33 Gr(math::vec3(y,y,y));
*/

	//float gamma = 100;
	
	math::vec3<double> e(a.x, a.y, a.z);
	
	float ke = 0.5;
	float ko = 3;
	
	//math::vec3 u = ((ac + I * a.w) * Gp + I * gamma * (1 - a.w)) * va * 0.5 - Gr * omega;
	math::vec3<double> u = -I * e * ke - omega * ko;
	
	raw_.torque_ = u;
		/*
		   

		// todo: make m dependent on direction of rotation
		float m = I.dot(math::vec3(1.0,0.0,0.0));

		float k = 10.0;
		float c = -2.0f * sqrt(m * k);
		pid_.coeff_p_ = k;
		pid_.coeff_d_ = c;


		math::quat q = actor->get_raw()->pose_.q;

		math::quat rot = q * raw_.q_target_.getConjugate();
		if(rot.magnitude() > 0)
		{
		float theta = -2.0 * acos(rot.w);

		theta = (theta > M_PI) ? (theta - 360.f) : theta;

		math::vec3 t(rot.x, rot.y, rot.z);
		t.normalize();

		// make sure getlinearvelocity is in actor-space
		
		float v = vel.dot(t);

		//q.print();
		//q_target_.print();


		//apply extra damping torque in all directions
		math::vec3 te = vel * 1.f * c;


		float fs = pid_.f(theta, v);
		t *= fs;

		//printf("theta = %f v = %f fs = %f\n", theta, v, fs);

		//printf("torque=\n");
		//t.print();

		raw_.torque_ = t + te;
		}
		 */
}
math::vec3<double> neb::control::rigid_body::control::f() {
	NEBULA_DEBUG_1_FUNCTION;

	switch(raw_.type_) {
		case neb::control::rigid_body::type::T0:
			return raw_.f_ * 100;
		case neb::control::rigid_body::type::T1:
			return raw_.force_;
		default:
			break;
	}
	return math::vec3<double>();
}
math::vec3<double> neb::control::rigid_body::control::t() {
	NEBULA_DEBUG_1_FUNCTION;

	switch(raw_.type_) {
		case neb::control::rigid_body::type::T0:
			return raw_.t_ * 3;
		case neb::control::rigid_body::type::T1:
			return raw_.torque_;
		default:
			break;
	}
	return math::vec3<double>();
}
void neb::control::rigid_body::control::print() {

	printf("torque\n");
	raw_.torque_.print();

	printf("force\n");
	raw_.force_.print();

}








