#include <gal/network/server.h>

#include <neb/config.h>
#include <neb/app.h>
#include <neb/physics.h>
#include <neb/simulation_callback.h>
#include <neb/packet/packet.h>
#include <neb/actor/Rigid_Body.h>

neb::actor::Rigid_Body::Rigid_Body():
	force_(0.0,0.0,0.0),
	torque_(0.0,0.0,0.0)
{}
int	neb::actor::Rigid_Body::key_fun(int key, int scancode, int action, int mods)
{
	printf("%s\n", __PRETTY_FUNCTION__);

	float force_scale = 100.0;
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
					force_ += x * force_scale;
					return 1;
				case GLFW_KEY_A:
					force_ -= x * force_scale;
					return 1;
				case GLFW_KEY_E:
					force_ += y * force_scale;
					return 1;
				case GLFW_KEY_Q:
					force_ -= y * force_scale;
					return 1;
				case GLFW_KEY_W:
					force_ -= z * force_scale;
					return 1;
				case GLFW_KEY_S:
					force_ += z * force_scale;
					return 1;
				case GLFW_KEY_I:
					torque_ += x * torque_scale;
					return 1;
				case GLFW_KEY_K:
					torque_ -= x * torque_scale;
					return 1;
				case GLFW_KEY_L:
					torque_ -= y * torque_scale;
					return 1;
				case GLFW_KEY_J:
					torque_ += y * torque_scale;
					return 1;
				case GLFW_KEY_O:
					torque_ -= z * torque_scale;
					return 1;
				case GLFW_KEY_U:
					torque_ += z * torque_scale;
					return 1;
				case GLFW_KEY_SPACE:
					fire();
					return 1;
				default:
					return 0;
			}
		case GLFW_RELEASE:
			switch(key)
			{
				case GLFW_KEY_D:
					force_ -= x * force_scale;
					return 1;
				case GLFW_KEY_A:
					force_ += x * force_scale;
					return 1;
				case GLFW_KEY_E:
					force_ -= y * force_scale;
					return 1;
				case GLFW_KEY_Q:
					force_ += y * force_scale;
					return 1;
				case GLFW_KEY_W:
					force_ += z * force_scale;
					return 1;
				case GLFW_KEY_S:
					force_ -= z * force_scale;
					return 1;
				case GLFW_KEY_I:
					torque_ -= x * torque_scale;
					return 1;
				case GLFW_KEY_K:
					torque_ += x * torque_scale;
					return 1;
				case GLFW_KEY_L:
					torque_ += y * torque_scale;
					return 1;
				case GLFW_KEY_J:
					torque_ -= y * torque_scale;
					return 1;
				case GLFW_KEY_O:
					torque_ += z * torque_scale;
					return 1;
				case GLFW_KEY_U:
					torque_ -= z * torque_scale;
					return 1;
				default:
					return 0;
			}
	}
	return 0;
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
	neb::packet::packet p;
/*
	p.type_ = neb::packet::ACTOR_FORCE;
	p.af.i_ = i_;
	p.af.f_[0] = force_.x;
	p.af.f_[1] = force_.y;
	p.af.f_[2] = force_.z;
	p.af.t_[0] = torque_.x;
	p.af.t_[1] = torque_.y;
	p.af.t_[2] = torque_.z;
*/
	gal::network::message::shared_t msg(new gal::network::message);

	memcpy(msg->body(), &p, sizeof(neb::packet::packet));
	msg->body_length(sizeof(neb::packet::packet));
	msg->encode_header();

	get_app()->client_->write(msg);
}
neb::actor::desc	neb::actor::Rigid_Body::get_projectile() {

	NEBULA_DEBUG_0_FUNCTION;

	neb::actor::desc desc;
	desc.reset();
	
	desc.type = neb::actor::RIGID_DYNAMIC;
	
	math::vec3 velocity(0.0, 0.0, -4.0);
	velocity = pose_.q.rotate(velocity);
	velocity += velocity_;
	desc.velocity.from_math(velocity);
	
	math::vec3 offset(0.0, 0.0, -2.0);
	offset = pose_.q.rotate(offset);

	auto pose = pose_;
	pose.p += offset;
	
	
	
	desc.pose.from_math(pose);

	
	desc.density = 1000.0;

	desc.filter_data_.simulation_.word0 = neb::filter::type::DYNAMIC;
	desc.filter_data_.simulation_.word1 = neb::filter::RIGID_AGAINST;
	
	glutpp::shape_desc sd;
	sd.box(math::vec3(0.1,0.1,0.1));
	
	sd.front_.reset();
	sd.front_.ambient_.from_math(math::black);
	sd.front_.diffuse_.from_math(math::red);
	sd.front_.emission_.from_math(math::black);
	
	desc.add_shape(sd);
	
	return desc;
}
neb::actor::desc	neb::actor::Rigid_Body::get_desc() {

	NEBULA_DEBUG_0_FUNCTION;
	
	neb::actor::desc desc = neb::actor::Base::get_desc();
	
	desc.velocity.from_math(velocity_);
	
	return desc;
}








