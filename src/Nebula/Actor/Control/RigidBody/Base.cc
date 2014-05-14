
#include <Nebula/Actor/Control/RigidBody/Base.hh>

Neb::Actor::Control::RigidBody::Base::Base() {

}
int Neb::Actor::Control::RigidBody::Base::key_fun(int key, int scancode, int action, int mods) {
	//NEBULA_DEBUG_0_FUNCTION;

	physx::PxVec3 x(1.0,0.0,0.0);
	physx::PxVec3 y(0.0,1.0,0.0);
	physx::PxVec3 z(0.0,0.0,1.0);

	switch(action)
	{
		case GLFW_PRESS:
			switch(key)
			{
				case GLFW_KEY_D:
					f_ += x;
					return 1;
				case GLFW_KEY_A:
					f_ -= x;
					return 1;
				case GLFW_KEY_E:
					f_ += y;
					return 1;
				case GLFW_KEY_Q:
					f_ -= y;
					return 1;
				case GLFW_KEY_W:
					f_ -= z;
					return 1;
				case GLFW_KEY_S:
					f_ += z;
					return 1;
				case GLFW_KEY_I:
					t_ += x;
					return 1;
				case GLFW_KEY_K:
					t_ -= x;
					return 1;
				case GLFW_KEY_L:
					t_ -= y;
					return 1;
				case GLFW_KEY_J:
					t_ += y;
					return 1;
				case GLFW_KEY_O:
					t_ -= z;
					return 1;
				case GLFW_KEY_U:
					t_ += z;
					return 1;
				default:
					return 0;
			}
		case GLFW_RELEASE:
			switch(key) {
				case GLFW_KEY_D:
					f_ -= x;
					return 1;
				case GLFW_KEY_A:
					f_ += x;
					return 1;
				case GLFW_KEY_E:
					f_ -= y;
					return 1;
				case GLFW_KEY_Q:
					f_ += y;
					return 1;
				case GLFW_KEY_W:
					f_ += z;
					return 1;
				case GLFW_KEY_S:
					f_ -= z;
					return 1;
				case GLFW_KEY_I:
					t_ -= x;
					return 1;
				case GLFW_KEY_K:
					t_ += x;
					return 1;
				case GLFW_KEY_L:
					t_ += y;
					return 1;
				case GLFW_KEY_J:
					t_ -= y;
					return 1;
				case GLFW_KEY_O:
					t_ += z;
					return 1;
				case GLFW_KEY_U:
					t_ -= z;
					return 1;
				default:
					return 0;
			}
	}


	return 0;
}
void Neb::Actor::Control::RigidBody::Manual::step(double dt) { // 0

}
void Neb::Actor::Control::RigidBody::PD::step(double dt) { // 1
	//NEBULA_DEBUG_1_FUNCTION;

	// step target

	float q_scale = 0.5;
	float p_scale = 0.5;

	if(t_.magnitude() == 0.0f)
	{
		//printf("no key\n");
	}
	else
	{
		physx::PxQuat rot(q_scale * dt, t_);

		q_target_ *= rot;

		//printf("q_target_=\n");
		//q_target_.print();


		p_target_ += f_ * p_scale;


		//printf("p_target_=\n");
		//p_target_.print();
	}

	// get actor
	auto base = actor_.lock();
	auto actor = base->isActorActor();
	assert(actor);
	
	auto pxrigidbody = actor->px_actor_->isRigidBody();


	// rotation from pose to target pose
	physx::PxQuat q = actor->pose_.q;
	physx::PxQuat a = q_target_.getConjugate() * q;




	// angular velocity
	physx::PxVec3 omega = pxrigidbody->getAngularVelocity();
	omega = q.rotate(omega);

	// inertia matrix
	//physx::PxVec3 vI = pxrigidbody->getMassSpaceInertiaTensor();
	
	//physx::PxMat33 I(vI);
	
	




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

	physx::PxVec3 e(a.x, a.y, a.z);

/*	float ke = 0.5;
	float ko = 3;
*/
	/** @todo replace with independent control system library */
	//math::vec3 u = ((ac + I * a.w) * Gp + I * gamma * (1 - a.w)) * va * 0.5 - Gr * omega;
	physx::PxVec3 u;// = -I * e * ke - omega * ko;

	torque_ = u;
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
physx::PxVec3 Neb::Actor::Control::RigidBody::Manual::f() {
	//NEBULA_DEBUG_1_FUNCTION;
	return f_ * 100;
}
physx::PxVec3 Neb::Actor::Control::RigidBody::Manual::t() {
	//NEBULA_DEBUG_1_FUNCTION;
	return t_ * 3;
}
physx::PxVec3 Neb::Actor::Control::RigidBody::PD::f() {
	//NEBULA_DEBUG_1_FUNCTION;
	return force_;
}
physx::PxVec3 Neb::Actor::Control::RigidBody::PD::t() {
	//NEBULA_DEBUG_1_FUNCTION;
	return torque_;
}
void Neb::Actor::Control::RigidBody::Base::print() {
/*
	printf("torque\n");
	torque_.print();

	printf("force\n");
	force_.print();
*/
}








