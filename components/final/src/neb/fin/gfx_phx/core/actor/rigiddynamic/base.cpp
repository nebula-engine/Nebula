#include <gal/log/log.hpp>

#include <neb/core/util/log.hpp>

#include <neb/fin/gfx_phx/core/actor/rigiddynamic/base.hpp>


neb::fin::gfx_phx::core::actor::rigiddynamic::base::base()
{
}
neb::fin::gfx_phx::core::actor::rigiddynamic::base::~base() {
	LOG(lg, neb::core::core::actor::sl, debug) << __PRETTY_FUNCTION__;
}
void					neb::fin::gfx_phx::core::actor::rigiddynamic::base::init(
		neb::core::core::actor::util::parent * const & p
		)
{
	LOG(lg, neb::core::core::actor::sl, debug) << __FUNCSIG__;

	setParent(p);

	neb::core::core::actor::base::init(p);

	neb::phx::core::actor::base::init(p);
	//neb::phx::core::actor::actor::base::init();
	//neb::phx::core::actor::rigidactor::base::init();
	//neb::phx::core::actor::rigidbody::base::init();
	//neb::phx::core::actor::rigiddynamic::base::init();

	neb::gfx::core::actor::base::init(p);

	neb::fin::gfx_phx::core::actor::base::init(p);
	//neb::fin::gfx_phx::core::actor::rigidactor::base::init();
}
void					neb::fin::gfx_phx::core::actor::rigiddynamic::base::release() {
	LOG(lg, neb::core::core::actor::sl, debug) << __PRETTY_FUNCTION__;

	neb::core::core::actor::base::release();

	//neb::phx::core::actor::base::release();
	neb::phx::core::actor::actor::base::release();
	//neb::phx::core::actor::rigidactor::base::release();
	//neb::phx::core::actor::rigidbody::base::release();
	//neb::phx::core::actor::rigiddynamic::base::release();

	neb::gfx::core::actor::base::release();

	neb::fin::gfx_phx::core::actor::base::release();
}
void					neb::fin::gfx_phx::core::actor::rigiddynamic::base::step(
		gal::etc::timestep const & ts) {
	neb::core::core::actor::base::step(ts);

	neb::phx::core::actor::base::step(ts);
	//neb::phx::core::actor::actor::base::step(ts);
	//neb::phx::core::actor::rigidactor::base::step(ts);
	neb::phx::core::actor::rigidbody::base::step(ts);
	//neb::phx::core::actor::rigiddynamic::base::step(ts);

	neb::gfx::core::actor::base::step(ts);

	neb::fin::gfx_phx::core::actor::base::step(ts);

}


