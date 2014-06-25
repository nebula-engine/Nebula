#include <stdio.h>

#include <Galaxy-Log/log.hpp>
#include <Galaxy-Network/message.hpp>

//#include <neb/gfx/window/Base.hh>
//#include <neb/gfx/Context/Base.hh>

#include <neb/debug.hh>
#include <neb/core/scene/Base.hh>
#include <neb/core/scene/Util/Types.hh>
#include <neb/core/scene/Util/Parent.hh>

#include <neb/core/actor/Base.hh>

#include <neb/core/light/Base.hh>
#include <neb/core/light/Spot.hh>
#include <neb/gfx/glsl/program.hh>
#include <neb/gfx/Camera/Projection/Perspective.hh>


#include <neb/core/actor/Util/Type.hh>
#include <neb/message/Actor/Event/Base.hh>
#include <neb/message/Actor/Create.hh>
#include <neb/message/Actor/Update.hh>
#include <neb/message/Actor/Event/Base.hh>

#include <neb/config.hh> // nebula/config.hpp.in
#include <neb/app/Base.hh>
//#include <neb/actor/free.hh>
#include <neb/core/actor/RigidDynamic/Base.hh>
#include <neb/core/actor/RigidStatic/Base.hh>
#include <neb/core/actor/Controller/Base.hh>
#include <neb/core/actor/Empty/Empty.hpp>
//#include <neb/actor/vehicle.hh>
#include <neb/core/actor/Empty/Empty.hpp>
#include <neb/core/shape/Base.hh>
#include <neb/core/shape/empty.hpp>
#include <neb/timer/Types.hh>
#include <neb/timer/Actor/Release.hpp>
#include <neb/gfx/glsl/Uniform/scalar.hpp>
#include <neb/core/light/Util/light_count.hpp>

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
void neb::core::scene::base::draw(sp::shared_ptr<neb::gfx::context::base> context, sp::shared_ptr<neb::glsl::program> p) {

	if(DEBUG_NEB) BOOST_LOG_CHANNEL_SEV(lg, "neb core scene", debug) << __PRETTY_FUNCTION__;

	//auto p = neb::app::base::globalBase()->use_program(neb::program_name::e::LIGHT);


	neb::core::light::util::count light_count;

	typedef neb::core::actor::util::parent A;

	A::map_.for_each<0>([&] (A::map_type::iterator<0> it) {
			auto actor = sp::dynamic_pointer_cast<neb::core::actor::base>(it->ptr_);
			assert(actor);
			actor->load_lights(light_count, neb::core::pose());
			});

	p->get_uniform_scalar("light_count_point")->load(light_count.point);
	p->get_uniform_scalar("light_count_spot")->load(light_count.spot);
	p->get_uniform_scalar("light_count_directional")->load(light_count.directional);

	//printf("%i\n",i);


	A::map_.for_each<0>([&] (A::map_type::iterator<0> it) {
			auto actor = sp::dynamic_pointer_cast<neb::core::actor::base>(it->ptr_);
			assert(actor);
			actor->draw(context, p, neb::core::pose());
			});

}
void						neb::core::scene::base::resize(int w, int h) {
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
sp::weak_ptr<neb::core::actor::rigidstatic::base>		neb::core::scene::base::createActorRigidStaticCube(neb::core::pose const & pose, real size) {

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
sp::weak_ptr<neb::core::actor::empty>				neb::core::scene::base::createActorLightPoint(vec3 p) {

	auto self(isSceneBase());

	auto actor = sp::make_shared<neb::core::actor::empty>(self);

	insert(actor);

	actor->init();

	// shape	
	/*
	   auto shape = sp::make_shared<neb::core::shape::empty>(actor);

	   actor->neb::core::shape::util::parent::insert(shape);

	   shape->init();
	 */
	auto shape = actor->neb::core::shape::util::parent::cii< neb::core::shape::empty, sp::shared_ptr<neb::core::actor::empty> >(actor);

	// light
	auto light = sp::make_shared<neb::Light::Point>(shape);

	shape->neb::Light::util::parent::insert(light);

	light->init();

	return actor;	
}




