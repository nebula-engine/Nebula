
#include <math/transform.hpp>

#include <galaxy/network/server.hpp>

#include <gru/renderable.hpp>
#include <gru/Camera/View/ridealong.hpp>

#include <nebula/config.hpp>
#include <nebula/app.hpp>
#include <nebula/physics.hpp>
#include <nebula/simulation_callback.hpp>
#include <nebula/actor/rigid_body/rigid_body.hpp>
#include <nebula/control/rigid_body/control.hpp>
#include <nebula/network/message.hpp>


neb::Actor::rigid_body::rigid_body::rigid_body(glutpp::parent_s parent):
	neb::Actor::RigidActor(parent),
	force_(0.0,0.0,0.0),
	torque_(0.0,0.0,0.0)
{}
void	neb::Actor::rigid_body::rigid_body::init(glutpp::actor::desc_s desc) {
	NEBULA_DEBUG_0_FUNCTION;
	
	neb::Actor::RigidActor::init(desc);

}
void neb::Actor::rigid_body::rigid_body::step_local(double time) {
	NEBULA_DEBUG_1_FUNCTION;
	
	neb::Actor::RigidActor::step_local(time);
	
	if(control_) control_->step_local(time);
	
	add_force(time);
}
void neb::Actor::rigid_body::rigid_body::step_remote(double time) {
	NEBULA_DEBUG_1_FUNCTION;
	
	auto app = get_app();
	
	gal::network::message::shared_t msg;
	neb::network::control::rigid_body::update_s control_update;
	
	neb::Actor::RigidActor::step_remote(time);
	
	
	
	if(control_)
	{
		gal::reset(msg);
		gal::reset(control_update);
		
		control_update->get_addr()->load_this(to_rigid_body());
		control_update->get_raw()->load(control_);
		
		msg->write(glutpp::network::type::CONTROL_UPDATE);
		control_update->write(msg);
		
		app->send_client(msg);
	}

}
void neb::Actor::rigid_body::rigid_body::add_force(double time) {
	NEBULA_DEBUG_1_FUNCTION;

	// non-user-controled
	math::vec3<double> f(force_);
	math::vec3<double> t(torque_);
	
	// user-controlled
	if(control_) {
		f += control_->f();
		t += control_->t();
	}
	
	math::transform pose = get_raw()->pose_;

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
glutpp::actor::desc_s neb::Actor::rigid_body::rigid_body::get_projectile() {
	NEBULA_DEBUG_0_FUNCTION;

	auto scene = get_scene();

	glutpp::actor::desc_s ad = scene->actors_deferred_[(char*)"proj0"];
	assert(ad);

	glutpp::actor::desc_s desc(new glutpp::actor::desc);
	*desc = *ad;

	// modify description	

	math::vec3<double> offset = desc->get_raw()->pose_.p;

	// pose
	math::transform pose(get_raw()->pose_);	
	offset = pose.q.rotate(offset);
	pose.p += offset;
	desc->get_raw()->pose_ = pose;
	
	// velocity
	math::vec3<double> velocity = desc->get_raw()->velocity_;
	velocity = pose.q.rotate(velocity);
	velocity += get_raw()->velocity_;
	desc->get_raw()->velocity_ = velocity;


	return desc;
}
void neb::Actor::rigid_body::rigid_body::print_info() {
	//NEBULA_DEBUG_1_FUNCTION;	

	neb::Actor::RigidActor::print_info();

	auto pxrb = px_actor_->isRigidBody();

	//math::transform pose		= pxrb->getCMassLocalPose();
	float mass			= pxrb->getMass();
	math::vec3<double> inertia		= pxrb->getMassSpaceInertiaTensor();
	math::vec3<double> linear_velocity	= pxrb->getLinearVelocity();
	math::vec3<double> angular_velocity	= pxrb->getAngularVelocity();


	printf("mass             = %f\n", mass);
	printf("interia          = "); inertia.print();
	printf("linear velocity  = "); linear_velocity.print();
	printf("angular velocity = "); angular_velocity.print();

}
void neb::Actor::rigid_body::rigid_body::create_control(neb::control::rigid_body::raw_s raw) {

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
		std::shared_ptr<glutpp::Camera::View::ridealong> cam(new glutpp::Camera::View::ridealong(me));
		wnd->renderable_->view_ = cam;

	}

}



