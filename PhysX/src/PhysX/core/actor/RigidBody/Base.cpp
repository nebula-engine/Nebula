/*
#include <Nebula/Network/server.hh>

#include <Nebula/Graphics/Context/Base.hh>
#include <Nebula/Graphics/Camera/View/ridealong.hh>

#include <Nebula/debug.hh>
#include <Nebula/Types.hh>
#include <Nebula/App/Base.hh>
//#include <Nebula/Physics.hh>
//#include <Nebula/simulation_callback.hh>

#include <Nebula/Actor/Util/Types.hh>
//#include <Nebula/Actor/Control/Util/Types.hh>
#include <Nebula/Actor/RigidBody/Base.hh>
#include <Nebula/Actor/RigidDynamic/Local.hh>

#include <Nebula/network/Types.hh>
#include <Nebula/network/message.hh>
#include <Nebula/Message/Actor/Control.hh>
#include <Nebula/Message/Types.hh>
*/
#include <PhysX/core/actor/control/rigidbody/base.hpp>
#include <PhysX/core/actor/rigidbody/base.hpp>

phx::core::actor::rigidbody::base::base(sp::shared_ptr<neb::core::actor::util::parent> parent):
	neb::core::actor::base(parent),
	neb::core::actor::actor::base(parent),
	neb::core::actor::rigidactor::base(parent),
	force_(0.0,0.0,0.0),
	torque_(0.0,0.0,0.0)
{}
void			phx::core::actor::rigidbody::base::init() {
	NEBULA_ACTOR_BASE_FUNC;
	
	neb::core::actor::rigidactor::base::init();
}
void			phx::core::actor::rigidbody::base::add_force(double time) {
	NEBULA_ACTOR_BASE_FUNC;

	// non-user-controled
	physx::PxVec3 f(force_);
	physx::PxVec3 t(torque_);
	
	// user-controlled
	if(control_) {
		f += control_->f();
		t += control_->t();
	}
	
	//physx::PxTransform pose = pose_;

	f = pose_.q.rotate(f);
	t = pose_.q.rotate(t);

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
sp::shared_ptr<neb::core::actor::base>		phx::core::actor::rigidbody::base::get_projectile() {
	NEBULA_ACTOR_BASE_FUNC;

	auto scene = getScene();

	sp::shared_ptr<neb::core::actor::rigiddynamic::local> actor(new neb::core::actor::rigiddynamic::local);

	//neb::core::actor::desc_w ad = scene->actors_deferred_[(char*)"proj0"];
	//assert(ad);

	//neb::core::actor::desc_u desc(new neb::core::actor::desc);
	//auto s = ad.lock();
	//assert(s);
	//*desc = *s;

	// modify description	

	physx::PxVec3 offset = pose_.p;

	// pose
	physx::PxTransform pose(pose_);	
	offset = pose.q.rotate(offset);
	pose.p += offset;
	pose_ = pose;
	
	// velocity
	physx::PxVec3 velocity = velocity_;
	velocity = pose.q.rotate(velocity);
	velocity += velocity_;
	velocity_ = velocity;
	
	return actor;
}
/*void neb::core::actor::rigidbody::base::create_control() {

	auto me = isRigidBody();

	neb::core::actor::Control::RigidBody::Control_u control(new neb::core::actor::Control::RigidBody::Control);
	neb::core::actor::Control::RigidBody::Control_w weak(control);

	
	control_ = control;

	control->actor_ = isBase();
	control->raw_.type_ = neb::core::actor::Control::RigidBody::Type::T0;


	auto wnd = window_.lock();
	if(wnd) {
		auto s = weak.lock();

		control->conn_.key_fun_ = wnd->sig_.key_fun_.connect(
				neb::Signals::KeyFun::slot_type(
					&neb::core::actor::Control::RigidBody::Control::key_fun,
					s.get(),
					_1,
					_2,
					_3,
					_4
					).track(s)
				);

		// camera control
		//std::shared_ptr<neb::Camera::View::ridealong> cam();
		
		sp::shared_ptr<neb::Camera::View::Ridealong> view(new neb::Camera::View::Ridealong(isBase()));
		
		wnd->renderable_->moveView(std::move(view));	
	}
}*/
void		phx::core::actor::rigidbody::base::step(double const & time, double const & dt) {
}



