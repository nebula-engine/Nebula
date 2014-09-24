
#include <gal/log/log.hpp>

#include <neb/core/util/log.hpp>
#include <neb/core/util/config.hpp>
#include <neb/core/util/debug.hpp>
#include <neb/core/util/decl.hpp>
#include <neb/core/core/actor/base.hpp>
#include <neb/core/core/actor/util/decl.hpp>
#include <neb/core/core/scene/base.hpp>

typedef neb::core::core::actor::base THIS;

neb::core::core::actor::base::base():
	density_(10.0),
	health_(1.0)
{



	LOG(lg, neb::core::core::actor::sl, debug) << __FUNCSIG__;
}
/*neb::core::core::actor::base::base(std::shared_ptr<neb::core::core::actor::util::parent> parent):
  gal::stl::child<parent_t>(parent.get()),
  density_(10.0)
  {
  LOG(lg, neb::core::core::actor::sl, debug) << __FUNCSIG__;
  assert(parent);
  }*/
neb::core::core::actor::base::~base() {
	LOG(lg, neb::core::core::actor::sl, debug) << __FUNCSIG__;

	assert(neb::core::core::actor::util::parent::map_.empty());
	assert(neb::core::core::shape::util::parent::map_.empty());

}
void		neb::core::core::actor::base::init(parent_t * const & p)
{
	LOG(lg, neb::core::core::actor::sl, debug) << __FUNCSIG__;

	neb::core::core::actor::util::parent::init(this);
	neb::core::core::shape::util::parent::init(this);
}
void		neb::core::core::actor::base::release() {
	LOG(lg, neb::core::core::actor::sl, debug) << __FUNCSIG__;

	gal::itf::__release::release();

	neb::core::core::actor::util::parent::clear();
	neb::core::core::shape::util::parent::clear();

}
/*std::shared_ptr<neb::core::core::actor::util::parent>	neb::core::core::actor::base::get_parent() {
  auto parent(parent_.lock());
  assert(parent);
  return parent;
  }*/
bool							neb::core::core::actor::base::hasScene() const
{
	LOG(lg, neb::core::core::actor::sl, debug) << __FUNCSIG__;

	if(!hasParent()) return false;

	auto scene = dynamic_cast<neb::core::core::scene::base*>(getParent());

	if(scene) return true;

	auto actor = dynamic_cast<neb::core::core::actor::base*>(getParent());

	assert(actor);

	return actor->hasScene();
}
neb::core::core::scene::base*				neb::core::core::actor::base::getScene() const
{
	LOG(lg, neb::core::core::actor::sl, debug) << __FUNCSIG__;

	assert(hasParent());

	auto scene = dynamic_cast<neb::core::core::scene::base*>(getParent());

	if(scene) return scene;

	auto actor = dynamic_cast<neb::core::core::actor::base*>(getParent());

	assert(actor);

	assert(actor != this);

	return actor->getScene();
}

neb::core::pose				neb::core::core::actor::base::getPose() const {
	return pose_;
}
neb::core::pose				neb::core::core::actor::base::getPoseGlobal() const {
	LOG(lg, neb::core::core::actor::sl, debug) << __FUNCSIG__;

	auto p = getParent()->getPoseGlobal() * getPose();

	return p;
}
void		neb::core::core::actor::base::setPose(neb::core::pose const & pose) {
	pose_ = pose;

	neb::core::core::shape::util::parent::callbackPose(pose);

	flag_.set(neb::core::core::actor::util::flag::E::SHOULD_UPDATE);
}
void		neb::core::core::actor::base::step(gal::etc::timestep const & ts) {
	LOG(lg, neb::core::core::actor::sl, debug) << __FUNCSIG__;

	//typedef neb::core::core::actor::util::parent A;

	actors::step(ts);
	shapes::step(ts);

	//A::map_.for_each([&] (A::map_type::iterator it) {
	//		it->ptr_->step(ts);
	//		});

	//S::map_.for_each([&] (S::map_type::iterator it) {
	//		it->ptr_->step(ts);
	//		});

}
weak_ptr<neb::core::core::shape::base>		neb::core::core::actor::base::createShapeCube(
		neb::core::pose pose, double size) {

	neb::core::core::shape::cuboid::desc desc(
			pose,
			glm::vec3(size)
			);

	auto shape = createShapeCuboid(desc);

	return shape;

}

weak_ptr<neb::core::core::shape::base>		neb::core::core::actor::base::createShapeLightSpot(
		neb::core::pose pose,
		glm::vec3 direction)
{
	auto shape = createShapeBase(pose).lock();

	shape->createLightSpot(direction);

	return shape;

}
void			THIS::load(ba::polymorphic_iarchive & ar, unsigned int const & v)
{
	//BOOST_SERIALIZATION_BASE_OBJECT_NVP(gal::itf::shared);
	//BOOST_SERIALIZATION_BASE_OBJECT_NVP(neb::core::core::actor::base);

	__serialize(ar, v);
}
void			THIS::save(ba::polymorphic_oarchive & ar, unsigned int const & v) const
{
	//BOOST_SERIALIZATION_BASE_OBJECT_NVP(gal::itf::shared);
	//BOOST_SERIALIZATION_BASE_OBJECT_NVP(neb::core::core::actor::base);

	const_cast<THIS*>(this)->__serialize(ar, v);
}










