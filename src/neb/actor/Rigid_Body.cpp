#include <gal/network/server.h>

#include <neb/config.h>
#include <neb/app.h>
#include <neb/physics.h>
#include <neb/simulation_callback.h>
#include <neb/packet/packet.h>
#include <neb/actor/Rigid_Body.h>

neb::actor::Rigid_Body::Rigid_Body(
		std::shared_ptr<neb::scene::scene> scene,
		std::shared_ptr<neb::actor::Base> actor):
	neb::actor::Rigid_Actor(scene, actor),
	force_(0.0,0.0,0.0),
	torque_(0.0,0.0,0.0)
{}
void	neb::actor::Rigid_Body::init(glutpp::actor::desc_s desc) {
	NEBULA_DEBUG_0_FUNCTION;
	
	neb::actor::Rigid_Actor::init(desc);

}
int	neb::actor::Rigid_Body::key_fun(int key, int scancode, int action, int mods) {
	NEBULA_DEBUG_0_FUNCTION;

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
void neb::actor::Rigid_Body::add_force() {
	NEBULA_DEBUG_1_FUNCTION;

	math::vec3 f(force_);
	math::vec3 t(torque_);

	math::transform pose = raw_.pose_;

	f = pose.q.rotate(f);
	t = pose.q.rotate(t);
	
	f.print();
	t.print();
	
	assert(px_actor_);
	physx::PxRigidBody* pxrigidbody = px_actor_->isRigidBody();
	assert(pxrigidbody);

	pxrigidbody->addForce(f);
	pxrigidbody->addTorque(t);
}
void	neb::actor::Rigid_Body::step_remote(double) {

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

	msg->set(&p, sizeof(neb::packet::packet));

	get_app()->client_->write(msg);
}
glutpp::actor::desc_s neb::actor::Rigid_Body::get_projectile() {
	NEBULA_DEBUG_0_FUNCTION;

	glutpp::actor::desc_s desc(new glutpp::actor::desc);

	desc->get_raw()->type_ = glutpp::actor::RIGID_DYNAMIC;

	math::transform pose(raw_.pose_);

	math::vec3 velocity(0.0, 0.0, -10.0);
	velocity = pose.q.rotate(velocity);
	velocity += raw_.velocity_;

	desc->get_raw()->velocity_ = velocity;

	math::vec3 offset(0.0, 0.0, -2.0);
	offset = pose.q.rotate(offset);

	pose.p += offset;

	desc->get_raw()->pose_ = pose;


	desc->get_raw()->density_ = 1000.0;

	desc->get_raw()->filter_data_.simulation_.word0 = glutpp::filter::type::DYNAMIC;
	desc->get_raw()->filter_data_.simulation_.word1 = glutpp::filter::RIGID_AGAINST;
	desc->get_raw()->filter_data_.simulation_.word2 = glutpp::filter::type::PROJECTILE;
	desc->get_raw()->filter_data_.simulation_.word3 = glutpp::filter::PROJECTILE_AGAINST;

	// shape
	glutpp::shape::desc_s sd(new glutpp::shape::desc);

	sd->get_raw()->box(math::vec3(0.1,0.1,0.1));

	sd->get_raw()->front_.reset();
	sd->get_raw()->front_.ambient_.from_math(math::black);
	sd->get_raw()->front_.diffuse_.from_math(math::red);
	sd->get_raw()->front_.emission_.from_math(math::black);

	desc->get_shapes()->vec_.push_back(std::make_tuple(sd));

	// light
	glutpp::light::desc_s ld(new glutpp::light::desc);

	ld->raw_.pos_.from_math(math::vec4(0.0, 0.0, 0.0, 1.0));
	ld->raw_.ambient_.from_math(math::black);
	ld->raw_.atten_linear_ = 2.0;

	sd->get_lights()->vec_.push_back(std::make_tuple(ld));

	//scene->create_light(ld, actor);

	return desc;
}









