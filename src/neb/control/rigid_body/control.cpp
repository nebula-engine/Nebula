#include <neb/control/rigid_body/control.h>

neb::control::rigid_body::control::control()
{

}
int neb::control::rigid_body::control::key_fun(int key, int scancode, int action, int mods) {
	NEBULA_DEBUG_0_FUNCTION;


	switch(raw_.type_) {
		case neb::control::rigid_body::type::T0:
			return key_fun0(key, action);
		case neb::control::rigid_body::type::T1:
			return key_fun1(key, action);
		default:
			break;
	}

	return 0;
}
int neb::control::rigid_body::control::key_fun0(int key, int action) {
	NEBULA_DEBUG_0_FUNCTION;

	float force_scale = 400.0;
	float torque_scale = 5.0;


	math::vec3 x(1.0,0.0,0.0);
	math::vec3 y(0.0,1.0,0.0);
	math::vec3 z(0.0,0.0,1.0);

	switch(action)
	{
		case GLFW_PRESS:
			switch(key)
			{
				case GLFW_KEY_D:
					raw_.force_ += x * force_scale;
					return 1;
				case GLFW_KEY_A:
					raw_.force_ -= x * force_scale;
					return 1;
				case GLFW_KEY_E:
					raw_.force_ += y * force_scale;
					return 1;
				case GLFW_KEY_Q:
					raw_.force_ -= y * force_scale;
					return 1;
				case GLFW_KEY_W:
					raw_.force_ -= z * force_scale;
					return 1;
				case GLFW_KEY_S:
					raw_.force_ += z * force_scale;
					return 1;
				case GLFW_KEY_I:
					raw_.torque_ += x * torque_scale;
					return 1;
				case GLFW_KEY_K:
					raw_.torque_ -= x * torque_scale;
					return 1;
				case GLFW_KEY_L:
					raw_.torque_ -= y * torque_scale;
					return 1;
				case GLFW_KEY_J:
					raw_.torque_ += y * torque_scale;
					return 1;
				case GLFW_KEY_O:
					raw_.torque_ -= z * torque_scale;
					return 1;
				case GLFW_KEY_U:
					raw_.torque_ += z * torque_scale;
					return 1;
				default:
					return 0;
			}
		case GLFW_RELEASE:
			switch(key)
			{
				case GLFW_KEY_D:
					raw_.force_ -= x * force_scale;
					return 1;
				case GLFW_KEY_A:
					raw_.force_ += x * force_scale;
					return 1;
				case GLFW_KEY_E:
					raw_.force_ -= y * force_scale;
					return 1;
				case GLFW_KEY_Q:
					raw_.force_ += y * force_scale;
					return 1;
				case GLFW_KEY_W:
					raw_.force_ += z * force_scale;
					return 1;
				case GLFW_KEY_S:
					raw_.force_ -= z * force_scale;
					return 1;
				case GLFW_KEY_I:
					raw_.torque_ -= x * torque_scale;
					return 1;
				case GLFW_KEY_K:
					raw_.torque_ += x * torque_scale;
					return 1;
				case GLFW_KEY_L:
					raw_.torque_ += y * torque_scale;
					return 1;
				case GLFW_KEY_J:
					raw_.torque_ -= y * torque_scale;
					return 1;
				case GLFW_KEY_O:
					raw_.torque_ += z * torque_scale;
					return 1;
				case GLFW_KEY_U:
					raw_.torque_ -= z * torque_scale;
					return 1;
				default:
					return 0;
			}
	}


	return 0;
}
int neb::control::rigid_body::control::key_fun1(int key, int action) {
	NEBULA_DEBUG_0_FUNCTION;

	math::vec3 dp;
	math::vec3 dq;

	float p_scale = 1.0;
	float q_scale = 0.5;

	math::vec3 x(1.0,0.0,0.0);
	math::vec3 y(0.0,1.0,0.0);
	math::vec3 z(0.0,0.0,1.0);
	
	//printf("%i %i\n", key, action);
	
	switch(action)
	{
		case GLFW_PRESS:
			switch(key)
			{
				case GLFW_KEY_D:
					dp += x;
					break;
				case GLFW_KEY_A:
					dp -= x;
					break;
				case GLFW_KEY_E:
					dp += y;
					break;
				case GLFW_KEY_Q:
					dp -= y;
					break;
				case GLFW_KEY_W:
					dp -= z;
					break;
				case GLFW_KEY_S:
					dp += z;
					break;
				case GLFW_KEY_I:
					dq += x;
					break;
				case GLFW_KEY_K:
					dq -= x;
					break;
				case GLFW_KEY_L:
					dq -= y;
					break;
				case GLFW_KEY_J:
					dq += y;
					break;
				case GLFW_KEY_O:
					dq -= z;
					break;
				case GLFW_KEY_U:
					dq += z;
					break;
				default:
					return 0;
			}
			break;
		case GLFW_RELEASE:
			switch(key)
			{
				case GLFW_KEY_D:
					dp -= x;
					break;
				case GLFW_KEY_A:
					dp += x;
					break;
				case GLFW_KEY_E:
					dp -= y;
					break;
				case GLFW_KEY_Q:
					dp += y;
					break;
				case GLFW_KEY_W:
					dp += z;
					break;
				case GLFW_KEY_S:
					dp -= z;
					break;
				case GLFW_KEY_I:
					dq -= x;
					break;
				case GLFW_KEY_K:
					dq += x;
					break;
				case GLFW_KEY_L:
					dq += y;
					break;
				case GLFW_KEY_J:
					dq -= y;
					break;
				case GLFW_KEY_O:
					dq += z;
					break;
				case GLFW_KEY_U:
					dq -= z;
					break;
				default:
					return 0;
			}
			break;
		default:
			return 0;
	}

	//printf("dq=\n");
	//dq.print();

	if(dq.magnitude() == 0.0f)
	{
		//printf("no key\n");
	}
	else
	{
		math::quat rot(q_scale, dq);

		raw_.q_target_ *= rot;

		printf("q_target_=\n");
		raw_.q_target_.print();


		raw_.p_target_ += dq * p_scale;


		//printf("p_target_=\n");
		//p_target_.print();
	}

	return 0;
}
void neb::control::rigid_body::control::step_local(double time) {
	NEBULA_DEBUG_1_FUNCTION;

	raw_.torque_ = math::vec3();

	assert(!actor_.expired());
	auto actor = std::dynamic_pointer_cast<neb::actor::Actor>(actor_.lock());

	auto pxrigidbody = actor->px_actor_->isRigidBody();

	math::vec3 I = pxrigidbody->getMassSpaceInertiaTensor();

	// todo: make m dependent on direction of rotation
	float m = I.dot(math::vec3(1.0,0.0,0.0));

	float k = 10.0;
	float c = -2.0f * sqrt(m * k);
	pid_.coeff_p_ = k;
	pid_.coeff_d_ = c;


	math::quat q = actor->raw_.pose_.q;

	math::quat rot = q * raw_.q_target_.getConjugate();
	if(rot.magnitude() > 0)
	{
		float theta = -2.0 * acos(rot.w);

		theta = (theta > M_PI) ? (theta - 360.f) : theta;

		math::vec3 t(rot.x, rot.y, rot.z);
		t.normalize();

		// make sure getlinearvelocity is in actor-space
		math::vec3 vel = pxrigidbody->getAngularVelocity();
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
}
math::vec3 neb::control::rigid_body::control::f() {
	NEBULA_DEBUG_1_FUNCTION;

	return raw_.force_;
}
math::vec3 neb::control::rigid_body::control::t() {
	NEBULA_DEBUG_1_FUNCTION;

	return raw_.torque_;
}
void neb::control::rigid_body::control::print() {
	
	printf("torque\n");
	raw_.torque_.print();
	
	printf("force\n");
	raw_.force_.print();

}








