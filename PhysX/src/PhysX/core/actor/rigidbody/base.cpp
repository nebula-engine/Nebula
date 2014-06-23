/*
#include <Nebula/net/server.hh>

#include <Nebula/gfx/Context/Base.hh>
#include <Nebula/gfx/Camera/View/ridealong.hh>

#include <Nebula/debug.hh>
#include <Nebula/util/decl.hpp>
#include <Nebula/app/Base.hh>
//#include <Nebula/Physics.hh>
//#include <Nebula/simulation_callback.hh>

#include <Nebula/core/actor/Util/Types.hh>
//#include <Nebula/core/actor/Control/Util/Types.hh>
#include <Nebula/core/actor/RigidBody/Base.hh>
#include <Nebula/core/actor/RigidDynamic/Local.hh>

#include <Nebula/network/Types.hh>
#include <Nebula/network/message.hh>
#include <Nebula/message/Actor/Control.hh>
#include <Nebula/message/Types.hh>
*/
#include <Galaxy-Log/log.hpp>

#include <Nebula/gfx/window/Base.hh>

#include <PhysX/util/convert.hpp>
#include <PhysX/core/scene/base.hpp>
#include <PhysX/core/actor/util/parent.hpp>
#include <PhysX/core/actor/control/rigidbody/base.hpp>
#include <PhysX/core/actor/rigiddynamic/local.hpp>


phx::core::actor::rigidbody::base::base(sp::shared_ptr<phx::core::actor::util::parent> parent):
	neb::core::actor::base(parent),
	neb::core::actor::actor::base(parent),
	neb::core::actor::rigidactor::base(parent),
	neb::core::actor::rigidbody::base(parent),
	phx::core::actor::base(parent),
	phx::core::actor::actor::base(parent),
	phx::core::actor::rigidactor::base(parent),
	force_(0.0,0.0,0.0),
	torque_(0.0,0.0,0.0)
{}
void			phx::core::actor::rigidbody::base::init() {

	BOOST_LOG_CHANNEL_SEV(lg, "phx core actor", debug) << __PRETTY_FUNCTION__;;
	
	neb::core::actor::rigidbody::base::init();
	phx::core::actor::rigidactor::base::init();
}
void			phx::core::actor::rigidbody::base::release() {

	BOOST_LOG_CHANNEL_SEV(lg, "phx core actor", debug) << __PRETTY_FUNCTION__;;

	neb::core::actor::rigidbody::base::release();
	phx::core::actor::rigidactor::base::release();
}
void			phx::core::actor::rigidbody::base::setPose(neb::core::pose const & pose) {

	BOOST_LOG_CHANNEL_SEV(lg, "phx core actor", debug) << __PRETTY_FUNCTION__;;

	neb::core::actor::rigidbody::base::setPose(pose);
	phx::core::actor::rigidactor::base::setPose(pose);
}
void			phx::core::actor::rigidbody::base::add_force(real time) {

	BOOST_LOG_CHANNEL_SEV(lg, "phx core actor", debug) << __PRETTY_FUNCTION__;;

	// non-user-controled
	//physx::PxVec3 f(force_[0],force_[1],force_[2]);
	//physx::PxVec3 t(torque_[0],torque_[1],torque_[2]);
	
	vec4 f(force_,1);
	vec4 t(torque_,1);

	// user-controlled
	if(control_) {
		f += control_->f();
		t += control_->t();
	}
	
	//physx::PxTransform pose = pose_;
	
	f = pose_.rot_ * f;//pose_.q.rotate(f);
	t = pose_.rot_ * t;//.q.rotate(t);

	assert(px_actor_);
	physx::PxRigidBody* pxrigidbody = px_actor_->isRigidBody();
	assert(pxrigidbody);


	BOOST_LOG_CHANNEL_SEV(lg, "phx core actor", debug)
		<< std::setw(8) << "f"
		<< std::setw(8) << f.x
		<< std::setw(8) << f.y
		<< std::setw(8) << f.z
		<< " mass " << pxrigidbody->getMass();



	
	
	pxrigidbody->addForce(phx::util::convert(vec3(f)));
	pxrigidbody->addTorque(phx::util::convert(vec3(t)));
}
void		phx::core::actor::rigidbody::base::create_control(sp::shared_ptr<neb::gfx::window::base> window) {

	//auto me = isRigidBodyBase();

	auto control(sp::make_shared<phx::core::actor::control::rigidbody::manual>());
	
	control_ = control;

	control->actor_ = isPxActorRigidBodyBase();
	
	control->conn_.key_fun_ = window->sig_.key_fun_.connect(
			20,
			neb::Signals::KeyFun::slot_type(
				&phx::core::actor::control::rigidbody::base::key_fun,
				control.get(),
				_1,
				_2,
				_3,
				_4,
				_5
				).track_foreign(control)
			);


}
void		phx::core::actor::rigidbody::base::step(gal::std::timestep const & ts) {

	BOOST_LOG_CHANNEL_SEV(lg, "phx core actor", debug) << __PRETTY_FUNCTION__;;

	if(control_) {
		control_->step(ts);
	}
	
	add_force(ts.dt);
}



