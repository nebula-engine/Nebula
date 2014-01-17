#include <math/transform.h>

#include <gal/network/server.h>

#include <glutpp/renderable.h>


#include <neb/config.h>
#include <neb/app.h>
#include <neb/physics.h>
#include <neb/simulation_callback.h>
#include <neb/actor/rigid_body/rigid_body.h>
#include <neb/control/rigid_body/control.h>
#include <neb/camera/ridealong.h>
#include <neb/network/message.h>


neb::actor::rigid_body::rigid_body::rigid_body(
		std::shared_ptr<neb::scene::scene> scene,
		std::shared_ptr<neb::actor::Base> actor):
	neb::actor::Rigid_Actor(scene, actor),
	force_(0.0,0.0,0.0),
	torque_(0.0,0.0,0.0)
{}
void	neb::actor::rigid_body::rigid_body::init(glutpp::actor::desc_s desc) {
	NEBULA_DEBUG_0_FUNCTION;
	
	neb::actor::Rigid_Actor::init(desc);

}
void neb::actor::rigid_body::rigid_body::step(double time) {
	neb::actor::Rigid_Actor::step(time);

	switch(mode_update_)
	{
		case glutpp::actor::mode_update::LOCAL:
			break;
		case glutpp::actor::mode_update::REMOTE:
			step_remote(time);
			break;
		default:
			break;
	}

}
void neb::actor::rigid_body::rigid_body::step_local(double time) {
	
	
	
}
void neb::actor::rigid_body::rigid_body::step_remote(double) {

	NEBULA_DEBUG_1_FUNCTION;

	if(control_)
	{

		gal::network::message::shared_t msg(new gal::network::message);

		neb::network::control::rigid_body::update_s control_update;

		control_update->get_addr()->load_this(to_rigid_body());
		control_update->get_raw()->load(control_);

	}

}
void neb::actor::rigid_body::rigid_body::add_force(double time) {
	NEBULA_DEBUG_1_FUNCTION;

	// non-user-controled
	math::vec3 f(force_);
	math::vec3 t(torque_);

	// user-controlled
	if(control_) {
		f += control_->f();
		t += control_->t(time);
	}

	math::transform pose = raw_.pose_;

	f = pose.q.rotate(f);
	t = pose.q.rotate(t);

	//printf("f = ");
	//f.print();
	//t.print();

	assert(px_actor_);
	physx::PxRigidBody* pxrigidbody = px_actor_->isRigidBody();
	assert(pxrigidbody);

	//printf("mass = %f\n", pxrigidbody->getMass());

	pxrigidbody->addForce(f);
	pxrigidbody->addTorque(t);
}
glutpp::actor::desc_s neb::actor::rigid_body::rigid_body::get_projectile() {
	NEBULA_DEBUG_0_FUNCTION;

	auto scene = get_scene();

	glutpp::actor::desc_s ad = scene->actors_deferred_[(char*)"proj0"];
	assert(ad);

	glutpp::actor::desc_s desc(new glutpp::actor::desc);
	*desc = *ad;

	// modify description	

	math::vec3 offset = desc->get_raw()->pose_.p;

	// pose
	math::transform pose(raw_.pose_);	
	offset = pose.q.rotate(offset);
	pose.p += offset;
	desc->get_raw()->pose_ = pose;

	// velocity
	math::vec3 velocity = desc->get_raw()->velocity_;
	velocity = pose.q.rotate(velocity);
	velocity += raw_.velocity_;
	desc->get_raw()->velocity_ = velocity;


	return desc;
}
void neb::actor::rigid_body::rigid_body::print_info() {
	//NEBULA_DEBUG_1_FUNCTION;	

	neb::actor::Rigid_Actor::print_info();

	auto pxrb = px_actor_->isRigidBody();

	//math::transform pose		= pxrb->getCMassLocalPose();
	float mass			= pxrb->getMass();
	math::vec3 inertia		= pxrb->getMassSpaceInertiaTensor();
	math::vec3 linear_velocity	= pxrb->getLinearVelocity();
	math::vec3 angular_velocity	= pxrb->getAngularVelocity();


	printf("mass             = %f\n", mass);
	printf("interia          = "); inertia.print();
	printf("linear velocity  = "); linear_velocity.print();
	printf("angular velocity = "); angular_velocity.print();

}
void neb::actor::rigid_body::rigid_body::create_control(neb::control::rigid_body::raw_s raw) {

	auto me = to_rigid_body();

	neb::control::rigid_body::control_s control(new neb::control::rigid_body::control);

	control_ = control;

	control->actor_ = me;
	control->raw_.type_ = neb::control::rigid_body::type::T0;


	if(!window_.expired())
	{
		auto wnd = window_.lock();

		control->conn_.key_fun_ = wnd->sig_.key_fun_.connect(std::bind(
					&neb::control::rigid_body::control::key_fun,
					control,
					std::placeholders::_1,
					std::placeholders::_2,
					std::placeholders::_3,
					std::placeholders::_4));



		// camera control
		std::shared_ptr<neb::camera::ridealong> cam(new neb::camera::ridealong(me));
		wnd->renderable_->camera_->control_ = cam;

	}

}



