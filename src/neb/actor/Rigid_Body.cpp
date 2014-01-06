#include <gal/network/server.h>

#include <neb/config.h>
#include <neb/app.h>
#include <neb/physics.h>
#include <neb/simulation_callback.h>
#include <neb/packet/packet.h>
#include <neb/actor/Rigid_Body.h>

neb::actor::Rigid_Body::Rigid_Body(
		glutpp::actor::desc_shared desc,
		std::shared_ptr<neb::scene::scene> scene,
		std::shared_ptr<neb::actor::Base> actor):
	neb::actor::Rigid_Actor(desc, scene, actor),
	force_(0.0,0.0,0.0),
	torque_(0.0,0.0,0.0)
{}
void	neb::actor::Rigid_Body::init() {
	
	neb::actor::Rigid_Actor::init();

}
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
	
	math::transform pose = desc_->raw_.pose_.to_math();
	
	f = pose.q.rotate(f);
	t = pose.q.rotate(t);

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
glutpp::actor::desc_shared neb::actor::Rigid_Body::get_projectile() {

	NEBULA_DEBUG_0_FUNCTION;
	
	glutpp::actor::desc_shared desc(new glutpp::actor::desc);
	
	desc->raw_.type_ = glutpp::actor::RIGID_DYNAMIC;
	
	math::transform pose(desc_->raw_.pose_.to_math());
	
	math::vec3 velocity(0.0, 0.0, -10.0);
	velocity = pose.q.rotate(velocity);
	velocity += velocity_;
	
	desc->raw_.velocity_.from_math(velocity);
	
	math::vec3 offset(0.0, 0.0, -2.0);
	offset = pose.q.rotate(offset);

	pose.p += offset;

	desc->raw_.pose_.from_math(pose);


	desc->raw_.density_ = 1000.0;

	desc->raw_.filter_data_.simulation_.word0 = glutpp::filter::type::DYNAMIC;
	desc->raw_.filter_data_.simulation_.word1 = glutpp::filter::RIGID_AGAINST;
	desc->raw_.filter_data_.simulation_.word2 = glutpp::filter::type::PROJECTILE;
	desc->raw_.filter_data_.simulation_.word3 = glutpp::filter::PROJECTILE_AGAINST;
	
	// shape
	glutpp::shape::desc_shared sd(new glutpp::shape::desc);

	sd->raw_.box(math::vec3(0.1,0.1,0.1));

	sd->raw_.front_.reset();
	sd->raw_.front_.ambient_.from_math(math::black);
	sd->raw_.front_.diffuse_.from_math(math::red);
	sd->raw_.front_.emission_.from_math(math::black);

	desc->shapes_.push_back(sd);

	// light
	glutpp::light::desc_shared ld(new glutpp::light::desc);

	ld->raw_.pos_.from_math(math::vec4(0.0, 0.0, 0.0, 1.0));
	ld->raw_.ambient_.from_math(math::black);
	ld->raw_.atten_linear_ = 2.0;

	sd->lights_.push_back(ld);

	//scene->create_light(ld, actor);

	return desc;
}
glutpp::actor::desc_shared neb::actor::Rigid_Body::get_desc() {

	NEBULA_DEBUG_0_FUNCTION;

	glutpp::actor::desc_shared desc = neb::actor::Base::get_desc();
	
	desc->raw_.velocity_.from_math(velocity_);

	return desc;
}








