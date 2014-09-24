
#include <stdio.h>

#include <gal/log/log.hpp>

#include <neb/core/util/debug.hpp>
#include <neb/core/util/config.hpp>
#include <neb/core/util/log.hpp>
#include <neb/core/core/actor/base.hpp>
<<<<<<< HEAD
=======
#include <neb/core/core/actor/rigidbody/desc.hpp>
>>>>>>> d0f62233eb8fed722542d3bfcc237575d904a507
#include <neb/core/core/actor/util/decl.hpp>
#include <neb/core/core/light/base.hpp>
#include <neb/core/core/light/util/light_count.hpp>
#include <neb/core/core/shape/base.hpp>
#include <neb/core/core/scene/base.hpp>
#include <neb/core/core/scene/util/decl.hpp>
#include <neb/core/core/scene/util/parent.hpp>

using namespace std;

<<<<<<< HEAD
neb::core::core::scene::base::base(std::shared_ptr<neb::core::core::scene::util::parent> parent):
	parent_(parent)
{
	LOG(lg, neb::core::core::scene::sl, debug) << __FUNCSIG__;
}
neb::core::core::scene::base::~base() {
	LOG(lg, neb::core::core::scene::sl, debug) << __FUNCSIG__;
}
void neb::core::core::scene::base::init() {
	LOG(lg, neb::core::core::scene::sl, debug) << __FUNCSIG__;
=======
typedef neb::core::core::scene::base THIS;

neb::core::core::scene::base::base():
	last_(0)
{
	LOG(lg, neb::core::core::scene::sl, debug) << __FUNCSIG__;
}
neb::core::core::scene::base::~base()
{
	LOG(lg, neb::core::core::scene::sl, debug) << __FUNCSIG__;
}
void neb::core::core::scene::base::init(parent_t * const & p)
{
	LOG(lg, neb::core::core::scene::sl, debug) << __FUNCSIG__;

	neb::core::core::actor::util::parent::init(this);
>>>>>>> d0f62233eb8fed722542d3bfcc237575d904a507
}
void neb::core::core::scene::base::release() {
	LOG(lg, neb::core::core::scene::sl, debug) << __FUNCSIG__;
	
	neb::core::core::actor::util::parent::clear();
}
<<<<<<< HEAD
neb::core::pose						neb::core::core::scene::base::getPose() {
	return neb::core::pose();
}		
neb::core::pose						neb::core::core::scene::base::getPoseGlobal() {
	return neb::core::pose();
}
weak_ptr<neb::core::core::scene::util::parent>		neb::core::core::scene::base::getParent() {
	return parent_;
}
void						neb::core::core::scene::base::add_deferred(std::shared_ptr<neb::core::core::actor::base> actor) {

	actors_deferred_[actor->name_] = actor;
}
void		neb::core::core::scene::base::step(gal::etc::timestep const & ts) {

	typedef neb::core::core::actor::util::parent A;

	A::map_.for_each<0>([&] (A::map_type::iterator<0> it) {
			auto actor = std::dynamic_pointer_cast<neb::core::core::actor::base>(it->ptr_);
			assert(actor);
			actor->step(ts);
			});
=======
neb::core::pose						neb::core::core::scene::base::getPose() const {
	return neb::core::pose();
}		
neb::core::pose						neb::core::core::scene::base::getPoseGlobal() const {
	return neb::core::pose();
}
void						neb::core::core::scene::base::add_deferred(std::shared_ptr<neb::core::core::actor::base> actor) {
	/** @todo deprecated */
	abort();
	//actors_deferred_[actor->name_] = actor;
}
void		neb::core::core::scene::base::step(gal::etc::timestep const & ts) {

	actors::step(ts);

//	A::map_.for_each([&] (A::map_type::pointer p) {
//			auto actor = std::dynamic_pointer_cast<neb::core::core::actor::base>(it->ptr_);
//			assert(actor);
//			actor->step(ts);
//			});
>>>>>>> d0f62233eb8fed722542d3bfcc237575d904a507

}
weak_ptr<neb::core::core::actor::base>		neb::core::core::scene::base::createActorRigidStaticCube(
		neb::core::pose pose,
		double size) {

	auto actor = createActorRigidStaticUninitialized().lock();
	actor->pose_ = pose;
<<<<<<< HEAD
	actor->init();
=======
	actor->init(this);
>>>>>>> d0f62233eb8fed722542d3bfcc237575d904a507

	// create shape

	auto shape = actor->createShapeCube(neb::core::pose(), size);

	// reinitialize in order to apply filtering to shape
	/// @todo consider implementing refresh-type function instead
<<<<<<< HEAD
	actor->init();

	return actor;
}
weak_ptr<neb::core::core::actor::base>		neb::core::core::scene::base::createActorRigidDynamicCube(
		neb::core::pose pose,
		double size) {

	auto actor = createActorRigidDynamicUninitialized().lock();
	actor->pose_ = pose;
	actor->init();

	// shape
	auto shape = actor->createShapeCube(neb::core::pose(), size);

	/// @todo consider implementing refresh-type function instead
	actor->init();
=======
	actor->init(this);

	return actor;
}
weak_ptr<neb::core::core::actor::base>		neb::core::core::scene::base::createActorRigidStaticCuboid(
		neb::core::pose pose,
		glm::vec3 size) {

	auto actor = createActorRigidStaticUninitialized().lock();
	actor->pose_ = pose;
	actor->init(this);
	
	// create shape
	
	auto shape = actor->createShapeCuboid(neb::core::core::shape::cuboid::desc(size));

	// reinitialize in order to apply filtering to shape
	/// @todo consider implementing refresh-type function instead
	actor->init(this);

	return actor;
}
weak_ptr<neb::core::core::actor::base>		neb::core::core::scene::base::createActorRigidDynamicCuboid(
		neb::core::core::actor::rigidbody::desc const &		actor_desc,
		neb::core::core::shape::cuboid::desc const &		shape_desc)
{

	auto actor = createActorRigidDynamicUninitialized().lock();

	actor->pose_ = actor_desc.pose;

	actor->init(this);

	// shape
	auto shape = actor->createShapeCuboid(shape_desc);

	/// @todo consider implementing refresh-type function instead
	actor->init(this);
>>>>>>> d0f62233eb8fed722542d3bfcc237575d904a507

	return actor;
}
weak_ptr<neb::core::core::actor::base>		neb::core::core::scene::base::createActorLightPoint(glm::vec3 p) {

	// actor
	auto actor = createActorBase(neb::core::pose(p)).lock();

	// shape	
	auto shape = actor->createShapeBase(neb::core::pose()).lock();

	// light
	auto light = shape->createLightPoint();

	return actor;	
}
<<<<<<< HEAD
=======
std::weak_ptr<neb::core::core::actor::base>		neb::core::core::scene::base::createActorLightDirectional(glm::vec3 p)
{
	auto actor = createActorBase(neb::core::pose()).lock();

	auto shape = actor->createShapeBase(neb::core::pose()).lock();

	auto light = shape->createLightDirectional(p);

	return actor;	
}
std::weak_ptr<neb::core::core::actor::base>		neb::core::core::scene::base::createActor(
		neb::core::core::actor::desc const * const & desc
		)
{
	assert(desc);
	return desc->visit(this);
}
void			THIS::addActor(
		std::shared_ptr<neb::core::core::actor::base> const & actor
		)
{
	insert(actor);
	actor->init(this);
}
void			THIS::load(
		boost::archive::polymorphic_iarchive & ar,
		unsigned int const & version)
{
	ar & boost::serialization::make_nvp("flag",flag_);
	ar & boost::serialization::make_nvp("actors",neb::core::core::actor::util::parent::map_);
}
void			THIS::save(
		boost::archive::polymorphic_oarchive & ar,
		unsigned int const & version) const
{
	ar & boost::serialization::make_nvp("flag",flag_);
	ar & boost::serialization::make_nvp("actors",neb::core::core::actor::util::parent::map_);
}
>>>>>>> d0f62233eb8fed722542d3bfcc237575d904a507



