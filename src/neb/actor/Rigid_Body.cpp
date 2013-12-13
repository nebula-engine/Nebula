#include <neb/actor/Rigid_Body.h>

neb::actor::Rigid_Body::Rigid_Body():
	force_(0.0,0.0,0.0),
	torque_(0.0,0.0,0.0)
{}
int	neb::actor::Rigid_Body::key_force(int scancode, int action, int mods, math::vec3 direction)
{
	float force_scale = 5.0;

	if(action == GLFW_PRESS) force_ += direction * force_scale;
	if(action == GLFW_RELEASE) force_ -= direction * force_scale;
	return 1;
}
int	neb::actor::Rigid_Body::key_torque(int scancode, int action, int mods, math::vec3 direction)
{
	float torque_scale = 2.0;
	
	if(action == GLFW_PRESS) torque_ += direction * torque_scale;
	if(action == GLFW_RELEASE) torque_ -= direction * torque_scale;
	return 1;
}
void	neb::actor::Rigid_Body::add_force()
{
	assert(px_actor_);

	math::vec3 f(force_);
	math::vec3 t(torque_);
	
	f = pose_.q.rotate(f);
	t = pose_.q.rotate(t);
	
	((physx::PxRigidBody*)px_actor_)->addForce(f);
	((physx::PxRigidBody*)px_actor_)->addTorque(t);
}



