

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

#include <PxPhysicsAPI.h>

#include <PhysX/core/actor/rigidbody/base.hpp>
#include <PhysX/core/actor/control/rigidbody/base.hpp>
#include <PhysX/util/convert.hpp>

phx::core::actor::control::rigidbody::base::base() {

}
int phx::core::actor::control::rigidbody::base::key_fun(sp::shared_ptr<neb::gfx::window::base> window, int key, int scancode, int action, int mods) {
	//NEBULA_DEBUG_0_FUNCTION;

	vec4 x(1.0,0.0,0.0,0);
	vec4 y(0.0,1.0,0.0,0);
	vec4 z(0.0,0.0,1.0,0);

	switch(action) {
		case GLFW_PRESS:
			switch(key) {
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
void		phx::core::actor::control::rigidbody::Manual::step(neb::core::TimeStep const & ts) { // 0

}


void		phx::core::actor::control::rigidbody::PD::step(neb::core::TimeStep const & ts) { // 1
	//NEBULA_DEBUG_1_FUNCTION;

	// step target

	float q_scale = 0.5;
	float p_scale = 0.5;

	if(glm::length(t_) == 0.0f)
	{
		//printf("no key\n");
	}
	else
	{
		//physx::PxQuat rot(q_scale * dt, phx::util::convert(t_));
		quat rot(q_scale * ts.dt, vec3(t_));

		q_target_ = q_target_ * rot;

		//printf("q_target_=\n");
		//q_target_.print();


		p_target_ += f_ * p_scale;


		//printf("p_target_=\n");
		//p_target_.print();
	}


/*
	// get actor
	auto base = actor_.lock();
	auto actor = actor_->isActorActor();
	assert(actor);
	
	auto pxrigidbody = actor->px_actor_->isRigidBody();
*/	
	auto pxrigidbody = actor_->px_actor_->isRigidBody();
	
	// rotation from pose to target pose
	quat q(actor_->pose_);
	
//	physx::PxQuat q = actor_->pose_.q;
	quat a = glm::conjugate(q_target_) * q;




	// angular velocity
	vec3 omega = phx::util::convert(pxrigidbody->getAngularVelocity());
	
	omega = q * omega;
	
	
	
	
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
	vec4 u;// = -I * e * ke - omega * ko;

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
vec4			phx::core::actor::control::rigidbody::Manual::f() {
	//NEBULA_DEBUG_1_FUNCTION;
	return f_ * 100.0f;
}
vec4			phx::core::actor::control::rigidbody::Manual::t() {
	//NEBULA_DEBUG_1_FUNCTION;
	return t_ * 3.0f;
}
vec4			phx::core::actor::control::rigidbody::PD::f() {
	//NEBULA_DEBUG_1_FUNCTION;
	return force_;
}
vec4			phx::core::actor::control::rigidbody::PD::t() {
	//NEBULA_DEBUG_1_FUNCTION;
	return torque_;
}








