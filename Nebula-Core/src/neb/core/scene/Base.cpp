#include <stdio.h>

#include <Galaxy-Log/log.hpp>
#include <Galaxy-Network/message.hpp>

//#include <neb/gfx/window/Base.hh>
//#include <neb/gfx/Context/Base.hh>

#include <neb/debug.hh>
#include <neb/core/scene/base.hpp>
#include <neb/core/scene/Util/Types.hh>
#include <neb/core/scene/Util/Parent.hh>

#include <neb/core/actor/base.hpp>

#include <neb/core/light/base.hpp>
//#include <neb/core/light/spot.hpp>


#include <neb/core/actor/Util/Type.hh>
/*#include <neb/message/Actor/Event/Base.hh>
#include <neb/message/Actor/Create.hh>
#include <neb/message/Actor/Update.hh>
#include <neb/message/Actor/Event/Base.hh>
*/
//#include <neb/config.hh> // nebula/config.hpp.in
//#include <neb/app/Base.hh>
//#include <neb/actor/free.hh>
//#include <neb/actor/vehicle.hh>
#include <neb/core/shape/base.hpp>
//#include <neb/timer/Types.hh>
//#include <neb/timer/Actor/Release.hpp>
//#include <neb/gfx/glsl/Uniform/scalar.hpp>
#include <neb/core/light/util/light_count.hpp>

neb::core::scene::base::base(sp::shared_ptr<neb::core::scene::util::parent> parent):
	parent_(parent)
{
	if(DEBUG_NEB) BOOST_LOG_CHANNEL_SEV(lg, "neb core scene", debug) << __PRETTY_FUNCTION__;
}
neb::core::scene::base::~base() {
	if(DEBUG_NEB) BOOST_LOG_CHANNEL_SEV(lg, "neb core scene", debug) << __PRETTY_FUNCTION__;
}
void neb::core::scene::base::init() {
	if(DEBUG_NEB) BOOST_LOG_CHANNEL_SEV(lg, "neb core scene", debug) << __PRETTY_FUNCTION__;
}
void neb::core::scene::base::release() {
	if(DEBUG_NEB) BOOST_LOG_CHANNEL_SEV(lg, "neb core scene", debug) << __PRETTY_FUNCTION__;
	
	neb::core::actor::util::parent::clear();
}
neb::core::pose					neb::core::scene::base::getPose() {
	return neb::core::pose();
}		
neb::core::pose					neb::core::scene::base::getPoseGlobal() {
	return neb::core::pose();
}
void		neb::core::scene::base::add_deferred(sp::shared_ptr<neb::core::actor::base> actor) {

	actors_deferred_[actor->name_] = actor;
}
void		neb::core::scene::base::step(gal::std::timestep const & ts) {

	typedef neb::core::actor::util::parent A;

	A::map_.for_each<0>([&] (A::map_type::iterator<0> it) {
			auto actor = sp::dynamic_pointer_cast<neb::core::actor::base>(it->ptr_);
			assert(actor);
			actor->step(ts);
			});

}
sp::weak_ptr<neb::core::actor::base>		neb::core::scene::base::createActorRigidStaticCube(neb::core::pose const & pose, real size) {

	auto actor = createActorRigidStaticUninitialized().lock();

	// set data members

	actor->pose_ = pose;

	// initialize (create physx)

	actor->init();

	// create shape

	auto shape = actor->createShapeCube(size);

	// reinitialize in order to apply filtering to shape
	/** @todo consider implementing refresh-type function instead */
	actor->init();

	return actor;
}
/*sp::weak_ptr<neb::core::actor::rigiddynamic::base>		neb::core::scene::base::createActorRigidDynamicCube(neb::core::pose const & pose, real size) {

  auto actor = createActorRigidDynamicUninitialized().lock();

// set data members

actor->pose_ = pose;

// initialize (create physx)

actor->init();

// create shape

auto shape = actor->createShapeCube(size);

// reinitialize in order to apply filtering to shape
 ** @todo consider implementing refresh-type function instead *
 actor->init();

 return actor;











 sp::shared_ptr<phx::core::actor::rigiddynamic::local>		create_actor_dynamic(sp::shared_ptr<phx::core::scene::local> scene) {

 auto actor = sp::make_shared<phx::core::actor::rigiddynamic::local>(scene);

 scene->insert(actor);

 actor->simulation_.word0 = phx::filter::filter::type::DYNAMIC;
 actor->simulation_.word1 = phx::filter::filter::RIGID_AGAINST;

 actor->init();

// shape	
auto shape = sp::make_shared<phx::core::shape::box>(actor);

actor->neb::core::shape::util::parent::insert(shape);

shape->init();

actor->setupFiltering();

std::cout << "actor dynamic use count = " << actor.use_count() << std::endl;

return actor;	
}







}*/
/*sp::weak_ptr<neb::core::actor::base>				neb::core::scene::base::createActorLightPoint(vec3 p) {

	auto self(isSceneBase());

	auto actor = sp::make_shared<neb::core::actor::base>(self);

	insert(actor);

	actor->init();

	// shape	
	auto shape = sp::make_shared<neb::core::shape::base>(actor);
	
	actor->neb::core::shape::util::parent::insert(shape);
	
	shape->init();

	
	// light
	
	shape->createLightPoint();
	

	return actor;	
}*/




