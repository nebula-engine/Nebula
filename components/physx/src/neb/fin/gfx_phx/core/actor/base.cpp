<<<<<<< HEAD
#include <neb/fin/gfx_phx/core/actor/base.hpp>
#include <neb/fin/gfx_phx/core/shape/box.hpp>

neb::fin::gfx_phx::core::actor::base::base(std::shared_ptr<neb::fin::gfx_phx::core::actor::util::parent> parent):
	neb::core::core::actor::base(parent),
	neb::phx::core::actor::base(parent),
	neb::gfx::core::actor::base(parent)
{
}
void						neb::fin::gfx_phx::core::actor::base::init() {
}
void						neb::fin::gfx_phx::core::actor::base::release() {
=======
#include <gal/stl/deleter.hpp>

#include <neb/fin/gfx_phx/core/actor/base.hpp>
#include <neb/fin/gfx_phx/core/shape/box.hpp>
#include <neb/phx/core/shape/HeightField.hpp>

typedef neb::fin::gfx_phx::core::actor::base THIS;

neb::fin::gfx_phx::core::actor::base::base()
{
}
void						THIS::init(neb::core::core::actor::util::parent* const & p)
{
	LOG(lg, neb::core::core::actor::sl, debug) << __FUNCSIG__;

	setParent(p);

	neb::core::core::actor::util::parent::init(this);
	neb::core::core::shape::util::parent::init(this);

	// base classes
	
	neb::core::core::actor::base::init(p);

	neb::phx::core::actor::base::init(p);

	//neb::gfx::core::actor::base::init(p);
}
void						neb::fin::gfx_phx::core::actor::base::release()
{
	neb::core::core::actor::base::release();
>>>>>>> d0f62233eb8fed722542d3bfcc237575d904a507
}
void						neb::fin::gfx_phx::core::actor::base::step(gal::etc::timestep const & ts) {
}
weak_ptr<neb::core::core::shape::base>		neb::fin::gfx_phx::core::actor::base::createShapeBase(neb::core::pose pose) {

	auto self(dynamic_pointer_cast<neb::fin::gfx_phx::core::actor::base>(shared_from_this()));

<<<<<<< HEAD
	auto actor(make_shared<neb::fin::gfx_phx::core::shape::base>(self));

	neb::fin::gfx_phx::core::shape::util::parent::insert(actor);
	actor->init();
	return actor;
}
weak_ptr<neb::core::core::shape::base>		neb::fin::gfx_phx::core::actor::base::createShapeBox(neb::core::pose pose, glm::vec3 size) {

	auto self(dynamic_pointer_cast<neb::fin::gfx_phx::core::actor::base>(shared_from_this()));

	auto actor(make_shared<neb::fin::gfx_phx::core::shape::box>(self));
	
	neb::fin::gfx_phx::core::shape::util::parent::insert(actor);
	actor->init();
	return actor;

}
=======
	typedef neb::fin::gfx_phx::core::shape::base T;

	std::shared_ptr<T> shape(new T(), gal::stl::deleter<T>());

	neb::core::core::shape::util::parent::insert(shape);
	
	shape->init(this);

	return shape;
}
weak_ptr<neb::core::core::shape::base>		neb::fin::gfx_phx::core::actor::base::createShapeCuboid(
		neb::core::core::shape::cuboid::desc desc)
{

	auto self(std::dynamic_pointer_cast<neb::fin::gfx_phx::core::actor::base>(shared_from_this()));

	typedef neb::fin::gfx_phx::core::shape::box T;

	std::shared_ptr<T> shape(new T(), gal::stl::deleter<T>());

	shape->pose_ = desc.pose_;
	shape->scale_ = desc.scale_;

	neb::core::core::shape::util::parent::insert(shape);
	
	shape->init(this);

	return shape;

}
std::weak_ptr<neb::core::core::shape::base>		neb::fin::gfx_phx::core::actor::base::createShapeHeightField(
					neb::core::core::shape::HeightField::desc const & desc)
{
	auto self(std::dynamic_pointer_cast<neb::fin::gfx_phx::core::actor::base>(shared_from_this()));

	typedef neb::phx::core::shape::HeightField T;
	
	std::shared_ptr<T> shape(new T(), gal::stl::deleter<T>());
	
	//shape->pose_ = desc.pose_;
	//shape->scale_ = desc.scale_;

	shape->desc_ = desc;

	neb::core::core::shape::util::parent::insert(shape);
	
	

	shape->init(this);

	return shape;
}
void			THIS::load(ba::polymorphic_iarchive & ar, unsigned int const & v)
{
	BOOST_SERIALIZATION_BASE_OBJECT_NVP(gal::itf::shared);
	BOOST_SERIALIZATION_BASE_OBJECT_NVP(neb::core::core::actor::base);

	//gal::itf::shared::load(ar, v);
	gal::itf::shared::serialize(ar, v);
	neb::core::core::actor::base::load(ar, v);
}
void			THIS::save(ba::polymorphic_oarchive & ar, unsigned int const & v) const
{
	BOOST_SERIALIZATION_BASE_OBJECT_NVP(gal::itf::shared);
	BOOST_SERIALIZATION_BASE_OBJECT_NVP(neb::core::core::actor::base);

	//gal::itf::shared::save(ar, v);
	const_cast<THIS*>(this)->gal::itf::shared::serialize(ar, v);
	neb::core::core::actor::base::save(ar, v);
}

>>>>>>> d0f62233eb8fed722542d3bfcc237575d904a507

