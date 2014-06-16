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
#include <Galaxy-Log/log.hpp>

#include <PhysX/util/convert.hpp>
#include <PhysX/core/scene/Base.hh>
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
	
	neb::core::actor::rigidactor::base::init();
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
	
	f = pose_ * f;//pose_.q.rotate(f);
	t = pose_ * t;//.q.rotate(t);

	//printf("f = ");
	//f.print();
	//t.print();

	assert(px_actor_);
	physx::PxRigidBody* pxrigidbody = px_actor_->isRigidBody();
	assert(pxrigidbody);
	
	//printf("mass = %f\n", pxrigidbody->getMass());
	
	pxrigidbody->addForce(phx::util::convert(vec3(f)));
	pxrigidbody->addTorque(phx::util::convert(vec3(t)));
}
sp::shared_ptr<phx::core::actor::rigiddynamic::local>		phx::core::actor::rigidbody::base::get_projectile() {
	BOOST_LOG_CHANNEL_SEV(lg, "phx core actor", debug) << __PRETTY_FUNCTION__;;
	
	auto parent(parent_.lock());

	sp::shared_ptr<phx::core::scene::base> scene = parent->getScene();
	
	auto actor(sp::make_shared<phx::core::actor::rigiddynamic::local>(scene));
	
	
	vec3 pos_relative(0,0,-2);
	vec4 vel_relative(0,0,-1,0);


	// pose
	
	mat4 pose(pose_);
	
	pose *= glm::translate(pos_relative);
	
	actor->pose_ = pose;
	
	// velocity
	
	vec3 vel(velocity_);
	
	vel_relative = pose * vel_relative;
	
	vel += vec3(vel_relative);
	
	actor->velocity_ = vel;
	
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
void		phx::core::actor::rigidbody::base::step(neb::core::TimeStep const & ts) {
}



