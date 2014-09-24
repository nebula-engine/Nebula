
#include <gal/log/log.hpp>

#include <neb/core/util/config.hpp>
#include <neb/core/util/log.hpp>
#include <neb/core/util/debug.hpp>
#include <neb/core/core/light/util/parent.hpp>
<<<<<<< HEAD
#include <neb/core/core/light/base.hpp>

neb::core::core::light::base::base(std::shared_ptr<neb::core::core::light::util::parent> parent):
	parent_(parent),
	pos_(glm::vec4(0.0, 0.0, 0.0, 1.0))
{}
void				neb::core::core::light::base::init() {
	LOG(lg, neb::core::core::light::sl, debug) << __FUNCSIG__;

}
void				neb::core::core::light::base::release() {
	LOG(lg, neb::core::core::light::sl, debug) << __FUNCSIG__;
}
void				neb::core::core::light::base::step(gal::etc::timestep const & ts) {

=======
#include <neb/core/core/shape/base.hpp>
#include <neb/core/core/light/base.hpp>

typedef neb::core::core::light::base THIS;

neb::core::core::light::base::base()
{
>>>>>>> d0f62233eb8fed722542d3bfcc237575d904a507
}
neb::core::pose			neb::core::core::light::base::getPose() {
	LOG(lg, neb::core::core::light::sl, debug) << __FUNCSIG__;
	
<<<<<<< HEAD
	auto parent(parent_.lock());
	assert(parent);
	
	auto p = parent->getPoseGlobal();
=======
	return pose_;
}
neb::core::pose			neb::core::core::light::base::getPoseGlobal()
{
	LOG(lg, neb::core::core::light::sl, debug) << __FUNCSIG__;
	
	auto p = getParent()->getPoseGlobal() * pose_;
>>>>>>> d0f62233eb8fed722542d3bfcc237575d904a507
	
	return p;
}
glm::vec4			neb::core::core::light::base::getPos() {
<<<<<<< HEAD
	return glm::vec4(pos_, 1.0);
}

=======
	return glm::vec4(pose_.pos_, 1.0);
}
bool				neb::core::core::light::base::hasScene() const
{
	if(!hasParent()) return false;

	auto shape = dynamic_cast<neb::core::core::shape::base*>(getParent());
	
	assert(shape);
	
	return shape->hasScene();
}
neb::core::core::scene::base*	neb::core::core::light::base::getScene()
{
	
	auto shape = dynamic_cast<neb::core::core::shape::base*>(getParent());
	
	assert(shape);
	
	return shape->getScene();
}
void		THIS::load(
		boost::archive::polymorphic_iarchive & ar,
		unsigned int const & version)
{
	serializeTemplate(ar, version);
	ar & BOOST_SERIALIZATION_NVP(pose_);
}
void		THIS::save(
		boost::archive::polymorphic_oarchive & ar,
		unsigned int const & version) const
{
	const_cast<THIS*>(this)->serializeTemplate(ar, version);
	ar & BOOST_SERIALIZATION_NVP(pose_);
}
>>>>>>> d0f62233eb8fed722542d3bfcc237575d904a507



