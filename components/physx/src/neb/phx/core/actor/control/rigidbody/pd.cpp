

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

#include <PxPhysicsAPI.h>

#include <neb/phx/core/actor/rigidbody/base.hpp>
#include <neb/phx/core/actor/control/rigidbody/base.hpp>
#include <neb/phx/util/convert.hpp>

vec3		neb::phx::core::actor::control::rigidbody::pd::getOrientationError() {
	// get actor
	auto actor = actor_.lock();
	assert(actor);
	
	
	// error
	quat qe = (q_target_ * glm::conjugate(actor->pose_.rot_));
	vec3 error(qe.x, qe.y, qe.z);
	
	return error;
}
void		neb::phx::core::actor::control::rigidbody::pd::step(gal::etc::timestep const & ts) { // 1
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

		p_target_ += f_ * p_scale;
	}


	//----------------------
	float p0 = -1.0;
	float p1 = -1.0;
	
	float c0 = -p0 - p1;
	//float c1 = p0 * p1;


	// get actor
	auto actor = actor_.lock();
	//auto actor = actor_->isActorActor();
	assert(actor);
	
	auto pxrigidbody = actor->px_actor_->isRigidBody();
	
	// rotation from pose to target pose
	quat q(actor->pose_.rot_);
	
	// error
	vec3 error(getOrientationError());
	
	
	// angular velocity
	vec3 omega = phx::util::convert(pxrigidbody->getAngularVelocity());
	
	omega = q * omega;
	
	physx::PxVec3 Ivec(pxrigidbody->getMassSpaceInertiaTensor());
	
	mat3 I;
	I[0][0] = Ivec.x;
	I[1][1] = Ivec.y;
	I[2][2] = Ivec.z;
	
	
	
	vec3 alpha = c0 * error;// - c1 * omega;
	
	
	// account for angular momentum
	torque_ = I * alpha; // + omega * (I * omega);

	//------------------------
	// force -----------------
	//------------------------
	{	
		//vec3 velocity = phx::util::convert(pxrigidbody->getLinearVelocity());

		physx::PxTransform trans = pxrigidbody->getGlobalPose();

		
		float c = 10.0;
		

		vec3 error = p_target_ - phx::util::convert(trans.p);

		force_ = c * error; // - c1 * velocity;
	}
}
vec3			neb::phx::core::actor::control::rigidbody::pd::f_body() {
	//NEBULA_DEBUG_1_FUNCTION;
	return vec3();
}
vec3			neb::phx::core::actor::control::rigidbody::pd::t_body() {
	//NEBULA_DEBUG_1_FUNCTION;
	return vec3();
}vec3			neb::phx::core::actor::control::rigidbody::pd::f_global() {
	//NEBULA_DEBUG_1_FUNCTION;
	return force_;
}
vec3			neb::phx::core::actor::control::rigidbody::pd::t_global() {
	//NEBULA_DEBUG_1_FUNCTION;
	return torque_;
}








