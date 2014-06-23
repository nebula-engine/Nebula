

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

#include <PxPhysicsAPI.h>

#include <PhysX/core/actor/rigidbody/base.hpp>
#include <PhysX/core/actor/control/rigidbody/base.hpp>
#include <PhysX/util/convert.hpp>


void		phx::core::actor::control::rigidbody::pd::step(gal::std::timestep const & ts) { // 1
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


	// get actor
	auto actor = actor_.lock();
	//auto actor = actor_->isActorActor();
	assert(actor);
	
	auto pxrigidbody = actor->px_actor_->isRigidBody();
	
	// rotation from pose to target pose
	quat q(actor->pose_.rot_);
	
	vec3 error = glm::axis(q_target_ * glm::conjugate(q));

	// angular velocity
	vec3 omega = phx::util::convert(pxrigidbody->getAngularVelocity());
	
	omega = q * omega;
	
	physx::PxVec3 Ivec(pxrigidbody->getMassSpaceInertiaTensor());
	
	mat3 I;
	I[0][0] = Ivec.x;
	I[1][1] = Ivec.y;
	I[2][2] = Ivec.z;
	
	
	float c0 = 1.0;
	float c1 = 1.0;
	
	vec3 alpha = c0 * error - c1 * omega;
	
	
	// account for angular momentum
	torque_ = vec4(I * alpha + omega * (I * omega), 0.0);

	//------------------------
	// force -----------------
	//------------------------
	{	
		vec3 velocity = phx::util::convert(pxrigidbody->getLinearVelocity());

		physx::PxTransform trans = pxrigidbody->getGlobalPose();



		vec3 error = vec3(p_target_) - phx::util::convert(trans.p);

		force_ = vec4(c0 * error - c1 * velocity, 1.0);
	}
}
vec4			phx::core::actor::control::rigidbody::pd::f() {
	//NEBULA_DEBUG_1_FUNCTION;
	return force_;
}
vec4			phx::core::actor::control::rigidbody::pd::t() {
	//NEBULA_DEBUG_1_FUNCTION;
	return torque_;
}








