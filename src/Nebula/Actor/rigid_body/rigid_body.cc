
#include <Nebula/network/server.hh>

#include <Nebula/Graphics/Context/Base.hh>
#include <Nebula/Graphics/Camera/View/ridealong.hh>

#include <Nebula/debug.hh>
#include <Nebula/Types.hh>
#include <Nebula/App/Base.hh>
#include <Nebula/physics.hh>
#include <Nebula/simulation_callback.hh>

#include <Nebula/Actor/Util/Types.hh>
#include <Nebula/Actor/rigid_body/rigid_body.hh>
#include <Nebula/Actor/Control/RigidBody/Base.hh>

#include <Nebula/network/Types.hh>
#include <Nebula/network/message.hh>
#include <Nebula/Message/Actor/Control.hh>
#include <Nebula/Message/Types.hh>

Neb::Actor::RigidBody::RigidBody::RigidBody(Neb::Actor::parent_w parent):
	Neb::Actor::RigidActor(parent),
	force_(0.0,0.0,0.0),
	torque_(0.0,0.0,0.0)
{}
void	Neb::Actor::RigidBody::RigidBody::init(Neb::Actor::desc_w desc) {
	NEBULA_ACTOR_BASE_FUNC;
	
	Neb::Actor::RigidActor::init(desc);

}
void Neb::Actor::RigidBody::RigidBody::step_local(double time) {
	NEBULA_ACTOR_BASE_FUNC;
	
	Neb::Actor::RigidActor::step_local(time);
	
	if(control_) control_->step_local(time);
	
	add_force(time);
}
void Neb::Actor::RigidBody::RigidBody::step_remote(double time) {
	NEBULA_ACTOR_BASE_FUNC;
	
	auto app = get_app();
	
	gal::network::omessage_s msg;

	Neb::Message::Actor::Control::RigidBody::Update_s control_update;
	
	Neb::Actor::RigidActor::step_remote(time);
	
	
	
	if(control_) {
		msg.reset(new gal::network::omessage);
		control_update.reset(new Neb::Message::Actor::Control::RigidBody::Update);
		
		control_update->addr_.load_this(isBase());
		control_update->raw_.load(control_);
		
		msg->write(Neb::network::type::CONTROL_UPDATE);
		
		control_update->serialize(msg->ar_, 0);
		
		app->send_client(msg);
	}

}
void Neb::Actor::RigidBody::RigidBody::add_force(double time) {
	NEBULA_ACTOR_BASE_FUNC;

	// non-user-controled
	physx::PxVec3 f(force_);
	physx::PxVec3 t(torque_);
	
	// user-controlled
	if(control_) {
		f += control_->f();
		t += control_->t();
	}
	
	physx::PxTransform pose = raw_->pose_;

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
Neb::Actor::desc_w	Neb::Actor::RigidBody::RigidBody::get_projectile() {
	NEBULA_ACTOR_BASE_FUNC;

	auto scene = get_scene();

	Neb::Actor::desc_w ad = scene->actors_deferred_[(char*)"proj0"];
	assert(ad);

	Neb::Actor::desc_u desc(new Neb::Actor::desc);
	auto s = ad.lock();
	assert(s);
	*desc = *s;

	// modify description	

	physx::PxVec3 offset = desc->raw_wrapper_.ptr_->pose_.p;

	// pose
	physx::PxTransform pose(raw_->pose_);	
	offset = pose.q.rotate(offset);
	pose.p += offset;
	desc->raw_wrapper_.ptr_->pose_ = pose;
	
	// velocity
	physx::PxVec3 velocity = desc->raw_wrapper_.ptr_->velocity_;
	velocity = pose.q.rotate(velocity);
	velocity += raw_->velocity_;
	desc->raw_wrapper_.ptr_->velocity_ = velocity;


	return desc;
}
void Neb::Actor::RigidBody::RigidBody::print_info() {
	//NEBULA_ACTOR_BASE_FUNC;	

	Neb::Actor::RigidActor::print_info();

//	auto pxrb = px_actor_->isRigidBody();

	//math::transform pose		= pxrb->getCMassLocalPose();
/*	float mass			= pxrb->getMass();
	physx::PxVec3 inertia		= pxrb->getMassSpaceInertiaTensor();
	physx::PxVec3 linear_velocity	= pxrb->getLinearVelocity();
	physx::PxVec3 angular_velocity	= pxrb->getAngularVelocity();
	*/
	/*
	   printf("mass             = %f\n", mass);
	   printf("interia          = "); inertia.print();
	   printf("linear velocity  = "); linear_velocity.print();
	   printf("angular velocity = "); angular_velocity.print();
	   */
}
void Neb::Actor::RigidBody::RigidBody::create_control(Neb::Actor::Control::RigidBody::Raw_s raw) {

	auto me = isRigidBody();

	Neb::Actor::Control::RigidBody::Control_u control(new Neb::Actor::Control::RigidBody::Control);
	Neb::Actor::Control::RigidBody::Control_w weak(control);

	
	control_ = control;

	control->actor_ = isBase();
	control->raw_.type_ = Neb::Actor::Control::RigidBody::Type::T0;


	auto wnd = window_.lock();
	if(wnd) {
		auto s = weak.lock();

		control->conn_.key_fun_ = wnd->sig_.key_fun_.connect(
				Neb::Signals::KeyFun::slot_type(
					&Neb::Actor::Control::RigidBody::Control::key_fun,
					s.get(),
					_1,
					_2,
					_3,
					_4
					).track(s)
				);



		// camera control
		//std::shared_ptr<Neb::Camera::View::ridealong> cam();
		
		Neb::Camera::View::Ridealong_s view(new Neb::Camera::View::Ridealong(isBase()));
		
		wnd->renderable_->moveView(std::move(view));
		
	}

}



