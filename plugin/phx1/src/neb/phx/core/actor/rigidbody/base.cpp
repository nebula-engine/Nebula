/*
#include <neb/net/server.hh>

#include <neb/gfx/Context/Base.hh>
#include <neb/gfx/camera/view/ridealong.hh>

#include <neb/debug.hh>
#include <neb/util/decl.hpp>
#include <neb/app/Base.hh>
//#include <neb/Physics.hh>
//#include <neb/simulation_callback.hh>

#include <neb/fnd/actor/util/Types.hh>
//#include <neb/fnd/actor/Control/util/Types.hh>
#include <neb/fnd/actor/RigidBody/Base.hh>
#include <neb/fnd/actor/RigidDynamic/Local.hh>

#include <neb/network/Types.hh>
#include <neb/network/message.hh>
#include <neb/message/Actor/Control.hh>
#include <neb/message/Types.hh>
*/
#include <gal/log/log.hpp>

#include <neb/fnd/util/debug.hpp>

//#include <neb/gfx/window/Base.hh>

#include <neb/fnd/input/signals.hpp>
#include <neb/fnd/core/actor/rigidbody/Base.hpp>

#include <neb/phx/util/convert.hpp>
#include <neb/phx/core/scene/base.hpp>
#include <neb/phx/core/actor/util/parent.hpp>
#include <neb/phx/core/actor/rigidbody/base.hpp>
#include <neb/phx/core/actor/control/rigidbody/base.hpp>

typedef neb::phx::core::actor::rigidbody::base THIS;

THIS::base():
	force_(0.0,0.0,0.0),
	torque_(0.0,0.0,0.0)
{
	printv_func(DEBUG);
}
void			neb::phx::core::actor::rigidbody::base::add_force(double time)
{
	printv_func(DEBUG);

	// body frame
	glm::vec3 f_body;
	glm::vec3 t_body;

	// global frame
	glm::vec3 f_global;
	glm::vec3 t_global;

	auto p = getParent();

	auto c = p->is_fnd_actor_rigidbody_base()->control_;
	
	if(c) {
		f_body += c->f_body();
		t_body += c->t_body();

		f_global += c->f_global();
		t_global += c->t_global();
	}
	
	
	// combine
	f_global += p->pose_.rot_ * f_body;
	t_global += p->pose_.rot_ * t_body;

	//physx::PxTransform pose = pose_;
	
	
	assert(px_actor_);
	physx::PxRigidBody* pxrigidbody = px_actor_->isRigidBody();
	assert(pxrigidbody);

	printv(DEBUG, "f_global %8f%8f%8f mass %8f",
		f_global.x,
		f_global.y,
		f_global.z,
		pxrigidbody->getMass());
	
	pxrigidbody->addForce(phx::util::convert(f_global));
	pxrigidbody->addTorque(phx::util::convert(t_global));
}
void		neb::phx::core::actor::rigidbody::base::step(gal::etc::timestep const & ts)
{
	printv_func(DEBUG);

	/*
	if(control_) {
		control_->step(ts);
	}
	*/

	add_force(ts.dt);
}
glm::vec3		THIS::get_angular_velocity()
{
	assert(px_actor_);
	auto rb = px_actor_->isRigidBody();
	assert(rb);
	
	physx::PxVec3 v(rb->getAngularVelocity());
	
	return glm::vec3(v.x,v.y,v.z);
}
glm::vec3		THIS::get_mass_space_inertia_tensor()
{
	assert(px_actor_);
	auto rb = px_actor_->isRigidBody();
	assert(rb);
	
	physx::PxVec3 v(rb->getMassSpaceInertiaTensor());
	
	return glm::vec3(v.x,v.y,v.z);
}



