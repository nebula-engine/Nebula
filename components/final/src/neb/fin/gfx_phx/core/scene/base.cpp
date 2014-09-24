//#include <neb/fin/gfx_phx/util/log.hpp>

#include <gal/stl/deleter.hpp>

#include <neb/core/util/log.hpp>

#include <neb/fin/gfx_phx/core/actor/rigidstatic/base.hpp>
#include <neb/fin/gfx_phx/core/actor/rigiddynamic/base.hpp>
#include <neb/fin/gfx_phx/core/scene/base.hpp>

typedef neb::fin::gfx_phx::core::scene::base THIS;

typedef weak_ptr<neb::core::core::actor::base>			wbase;

neb::fin::gfx_phx::core::scene::base::base()
{
}
void		neb::fin::gfx_phx::core::scene::base::init(parent_t * const & p)
{
	std::cout << __PRETTY_FUNCTION__ << std::endl;

	neb::phx::core::scene::base::init(p);
	neb::core::core::scene::base::init(p);
}
void		neb::fin::gfx_phx::core::scene::base::release() {
	std::cout << __PRETTY_FUNCTION__ << std::endl;

	neb::core::core::scene::base::release();

	neb::phx::core::scene::base::release();
}
void		neb::fin::gfx_phx::core::scene::base::step(gal::etc::timestep const & ts) {
	//std::cout << __PRETTY_FUNCTION__ << std::endl;
	neb::core::core::scene::base::step(ts);
	neb::phx::core::scene::base::step(ts);
}
wbase		neb::fin::gfx_phx::core::scene::base::createActorBase(neb::core::pose pose) {

	auto self(dynamic_pointer_cast<neb::fin::gfx_phx::core::scene::base>(shared_from_this()));

	typedef neb::fin::gfx_phx::core::actor::base T;

	std::shared_ptr<T> actor(new T(), gal::stl::deleter<T>());

	actor->pose_ = pose;

	insert(actor);

	actor->init(this);

	return actor;
}
wbase		neb::fin::gfx_phx::core::scene::base::createActorRigidStaticUninitialized()
{
	LOG(lg, neb::core::core::scene::sl, debug) << __PRETTY_FUNCTION__;


	auto self(dynamic_pointer_cast<neb::fin::gfx_phx::core::scene::base>(shared_from_this()));

	typedef neb::fin::gfx_phx::core::actor::rigidstatic::base T;

	std::shared_ptr<T> actor(new T(), gal::stl::deleter<T>());

	neb::core::core::actor::util::parent::insert(actor);

	actor->simulation_.word0 = phx::filter::filter::type::STATIC;
	actor->simulation_.word1 = phx::filter::filter::RIGID_AGAINST;
	actor->simulation_.word2 = phx::filter::filter::type::STATIC;
	actor->simulation_.word3 = phx::filter::filter::type::PROJECTILE;

	return actor;
}
wbase		neb::fin::gfx_phx::core::scene::base::createActorRigidDynamicUninitialized()
{
	LOG(lg, neb::core::core::scene::sl, debug) << __PRETTY_FUNCTION__;


	auto self(dynamic_pointer_cast<neb::fin::gfx_phx::core::scene::base>(shared_from_this()));

	typedef neb::fin::gfx_phx::core::actor::rigiddynamic::base T;

	std::shared_ptr<T> actor(new T(), gal::stl::deleter<T>());

	neb::core::core::actor::util::parent::insert(actor);

	actor->simulation_.word0 = phx::filter::filter::type::DYNAMIC;
	actor->simulation_.word1 = phx::filter::filter::RIGID_AGAINST;
	actor->simulation_.word2 = phx::filter::filter::type::DYNAMIC;
	actor->simulation_.word3 = phx::filter::filter::type::PROJECTILE;

	return actor;

}
wbase			neb::fin::gfx_phx::core::scene::base::createActorRigidDynamic(
		neb::core::core::actor::rigiddynamic::desc const * const & desc
		)
{
	LOG(lg, neb::core::core::scene::sl, debug) << __PRETTY_FUNCTION__;


	auto self(dynamic_pointer_cast<neb::fin::gfx_phx::core::scene::base>(shared_from_this()));

	typedef neb::fin::gfx_phx::core::actor::rigiddynamic::base T;

	std::shared_ptr<T> actor(new T(), gal::stl::deleter<T>());

	neb::core::core::actor::util::parent::insert(actor);

	actor->simulation_.word0 = phx::filter::filter::type::DYNAMIC;
	actor->simulation_.word1 = phx::filter::filter::RIGID_AGAINST;
	actor->simulation_.word2 = phx::filter::filter::type::DYNAMIC;
	actor->simulation_.word3 = phx::filter::filter::type::PROJECTILE;

	actor->init(this);

	return actor;

}

typedef neb::core::core::scene::base Base1;
typedef neb::phx::core::scene::base Base2;

void		THIS::load(boost::archive::polymorphic_iarchive & ar, unsigned int const & version)
{
	LOG(lg, neb::core::core::scene::sl, debug) << __PRETTY_FUNCTION__;

	//BOOST_SERIALIZATION_BASE_OBJECT_NVP(Base1);
	//BOOST_SERIALIZATION_BASE_OBJECT_NVP(Base2);
	BOOST_SERIALIZATION_BASE_OBJECT_NVP(neb::core::core::scene::base);
	BOOST_SERIALIZATION_BASE_OBJECT_NVP(neb::phx::core::scene::base);

	neb::core::core::scene::base::load(ar, version);
	neb::phx::core::scene::base::load(ar, version);
}
void		THIS::save(boost::archive::polymorphic_oarchive & ar, unsigned int const & version) const
{
	LOG(lg, neb::core::core::scene::sl, debug) << __PRETTY_FUNCTION__;

	//BOOST_SERIALIZATION_BASE_OBJECT_NVP(Base1);
	//BOOST_SERIALIZATION_BASE_OBJECT_NVP(Base2);
	BOOST_SERIALIZATION_BASE_OBJECT_NVP(neb::core::core::scene::base);
	BOOST_SERIALIZATION_BASE_OBJECT_NVP(neb::phx::core::scene::base);

	neb::core::core::scene::base::save(ar, version);
	neb::phx::core::scene::base::save(ar, version);
}

