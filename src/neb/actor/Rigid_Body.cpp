#include <gal/network/server.h>

#include <neb/app.h>
#include <neb/packet/packet.h>
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
void	neb::actor::Rigid_Body::step_remote(double)
{
	neb::packet p;
	p.type_ = neb::packet::ACTOR_FORCE;
	p.af.i_ = i_;
	p.af.f_[0] = force_.x;
	p.af.f_[1] = force_.y;
	p.af.f_[2] = force_.z;
	p.af.t_[0] = torque_.x;
	p.af.t_[1] = torque_.y;
	p.af.t_[2] = torque_.z;
	
	gal::network::message::shared_t msg(new gal::network::message);
	
	memcpy(msg->body(), &p, sizeof(neb::packet));
	msg->body_length(sizeof(neb::packet));
	msg->encode_header();
	
	get_app()->client_->write(msg);
}




