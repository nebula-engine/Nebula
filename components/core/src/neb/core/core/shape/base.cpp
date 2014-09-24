#include <glm/gtx/transform.hpp>

#include <gal/stl/map.hpp>

#include <gal/log/log.hpp>

#include <neb/core/math/geo/polygon.hpp>
#include <neb/core/util/config.hpp>
#include <neb/core/util/log.hpp>
#include <neb/core/util/debug.hpp>
<<<<<<< HEAD
#include <neb/core/core/shape/base.hpp>
#include <neb/core/core/light/base.hpp>

neb::core::core::shape::base::base(std::shared_ptr<neb::core::core::shape::util::parent> parent):
	parent_(parent),
	s_(1,1,1)
{
	LOG(lg, neb::core::core::shape::sl, debug) << __FUNCSIG__;
	assert(parent);
}
neb::core::core::shape::base::~base() {}
neb::core::pose				neb::core::core::shape::base::getPoseGlobal() {
	LOG(lg, neb::core::core::shape::sl, debug) << __FUNCSIG__;
	
	neb::core::pose m;
	
	auto parent = parent_.lock();
	if(parent) {
		m = parent->getPoseGlobal() * getPose();
	} else {
		m = getPose();
	}

	return m;
}
neb::core::pose				neb::core::core::shape::base::getPose() {
	return pose_;
}
void					neb::core::core::shape::base::init() {
	LOG(lg, neb::core::core::shape::sl, debug) << __FUNCSIG__;

	auto me = std::dynamic_pointer_cast<neb::core::core::shape::base>(shared_from_this());
=======
#include <neb/core/core/actor/base.hpp>
#include <neb/core/core/shape/base.hpp>
#include <neb/core/core/light/base.hpp>

typedef neb::core::core::shape::base THIS;

neb::core::core::shape::base::base():
	scale_(1.0)
{
	LOG(lg, neb::core::core::shape::sl, debug) << __FUNCSIG__;
}
neb::core::core::shape::base::~base()
{
	LOG(lg, neb::core::core::shape::sl, info) << __FUNCSIG__;
}

bool							neb::core::core::shape::base::hasScene()
{
	if(!hasParent()) return false;

	auto shape = dynamic_cast<neb::core::core::shape::base*>(getParent());
	
	if(shape) return shape->hasScene();

	auto actor = dynamic_cast<neb::core::core::actor::base*>(getParent());

	assert(actor);
	
	return actor->hasScene();
}

neb::core::core::scene::base*				neb::core::core::shape::base::getScene()
{
	auto shape = dynamic_cast<neb::core::core::shape::base*>(getParent());
	
	if(shape) return shape->getScene();

	auto actor = dynamic_cast<neb::core::core::actor::base*>(getParent());

	assert(actor);
	
	return actor->getScene();
}


neb::core::pose				neb::core::core::shape::base::getPoseGlobal() const {
	LOG(lg, neb::core::core::shape::sl, debug) << __FUNCSIG__;
	
	return getParent()->getPoseGlobal() * pose_;
}
neb::core::pose				neb::core::core::shape::base::getPose() const {
	return pose_;
}
void					neb::core::core::shape::base::__callbackPose(neb::core::pose const & gpose) {
	auto pose = gpose * pose_;
	neb::core::core::shape::util::parent::callbackPose(pose);
	neb::core::core::light::util::parent::callbackPose(pose);
}
void					neb::core::core::shape::base::init(neb::core::core::shape::util::parent * const & p)
{
	LOG(lg, neb::core::core::shape::sl, debug) << __FUNCSIG__;
	
	setParent(p);
	
	//auto me = std::dynamic_pointer_cast<neb::core::core::shape::base>(shared_from_this());

>>>>>>> d0f62233eb8fed722542d3bfcc237575d904a507
	//auto scene = get_parent()->get_scene();

	// type

	// program
<<<<<<< HEAD
/*	if(image_.length() == 0) {
		program_ = neb::program_name::LIGHT;
	} else {
		** @todo replace this with something better... *
		//flag_.set(neb::core::core::shape::flag::e::IMAGE);

		program_ = neb::program_name::IMAGE;
	}
*/

	neb::core::core::shape::util::parent::init();
	neb::core::core::light::util::parent::init();

}
void					neb::core::core::shape::base::release() {
	LOG(lg, neb::core::core::shape::sl, debug) << __FUNCSIG__;

	//neb::util::parent<neb::core::core::shape::base>::release();
	neb::core::core::shape::util::parent::release();
	neb::core::core::light::util::parent::release();
=======
	/*	if(image_.length() == 0) {
		program_ = neb::program_name::LIGHT;
		} else {
	 ** @todo replace this with something better... *
	//flag_.set(neb::core::core::shape::flag::e::IMAGE);

	program_ = neb::program_name::IMAGE;
	}
	*/

	neb::core::core::shape::util::parent::init(this);
	neb::core::core::light::util::parent::init(this);

}
void					neb::core::core::shape::base::release()
{
	LOG(lg, neb::core::core::shape::sl, debug) << __FUNCSIG__;

	neb::core::core::shape::util::parent::map_.clear();
	neb::core::core::light::util::parent::map_.clear();
>>>>>>> d0f62233eb8fed722542d3bfcc237575d904a507
}
void						neb::core::core::shape::base::step(
		gal::etc::timestep const & ts)
{
	neb::core::core::shape::util::parent::step(ts);
	neb::core::core::light::util::parent::step(ts);
}
<<<<<<< HEAD
=======
void	THIS::load(ba::polymorphic_iarchive & ar, unsigned int const & v)
{
	LOG(lg, neb::core::core::shape::sl, debug) << __FUNCSIG__;
	__serialize(ar, v);
}
void	THIS::save(ba::polymorphic_oarchive & ar, unsigned int const & v) const
{
	LOG(lg, neb::core::core::shape::sl, debug) << __FUNCSIG__;
	const_cast<THIS*>(this)->__serialize(ar, v);
}





>>>>>>> d0f62233eb8fed722542d3bfcc237575d904a507

