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

#include <Nebula/debug.hh>
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

	if(DEBUG_NEB) BOOST_LOG_CHANNEL_SEV(lg, "phx core actor", debug) << __PRETTY_FUNCTION__;;
	
	neb::core::actor::rigidbody::base::init();
	phx::core::actor::rigidactor::base::init();
}
/*void			phx::core::actor::rigidbody::base::release() {

	if(DEBUG_NEB) BOOST_LOG_CHANNEL_SEV(lg, "phx core actor", debug) << __PRETTY_FUNCTION__;;

	neb::core::actor::rigidbody::base::release();
	phx::core::actor::rigidactor::base::release();
}*/
void			phx::core::actor::rigidbody::base::setPose(neb::core::pose const & pose) {

	if(DEBUG_NEB) BOOST_LOG_CHANNEL_SEV(lg, "phx core actor", debug) << __PRETTY_FUNCTION__;;

	neb::core::actor::rigidbody::base::setPose(pose);
	phx::core::actor::rigidactor::base::setPose(pose);
}
void			phx::core::actor::rigidbody::base::add_force(real time) {

	if(DEBUG_NEB) BOOST_LOG_CHANNEL_SEV(lg, "phx core actor", debug) << __PRETTY_FUNCTION__;;

	// body frame
	vec3 f_body;
	vec3 t_body;

	// global frame
	vec3 f_global;
	vec3 t_global;
	
	if(control_) {
		f_body += control_->f_body();
		t_body += control_->t_body();

		f_global += control_->f_global();
		t_global += control_->t_global();
	}

	
	// combine
	f_global += pose_.rot_ * f_body;
	t_global += pose_.rot_ * t_body;

	//physx::PxTransform pose = pose_;
	
	
	assert(px_actor_);
	physx::PxRigidBody* pxrigidbody = px_actor_->isRigidBody();
	assert(pxrigidbody);


	if(DEBUG_NEB) BOOST_LOG_CHANNEL_SEV(lg, "phx core actor", debug)
		<< std::setw(8) << "f_global"
		<< std::setw(8) << f_global.x
		<< std::setw(8) << f_global.y
		<< std::setw(8) << f_global.z
		<< " mass " << pxrigidbody->getMass();


	
	pxrigidbody->addForce(phx::util::convert(f_global));
	pxrigidbody->addTorque(phx::util::convert(t_global));
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

	if(DEBUG_NEB) BOOST_LOG_CHANNEL_SEV(lg, "phx core actor", debug) << __PRETTY_FUNCTION__;;

	if(control_) {
		control_->step(ts);
	}
	
	add_force(ts.dt);
}



