#include <gal/log/log.hpp>

#include <neb/core/util/log.hpp>

#include <neb/fin/gfx_phx/core/actor/rigidstatic/base.hpp>

neb::fin::gfx_phx::core::actor::rigidstatic::base::base(std::shared_ptr<neb::fin::gfx_phx::core::actor::util::parent> parent):
	neb::core::core::actor::base(parent),
	neb::phx::core::actor::base(parent),
	neb::phx::core::actor::actor::base(parent),
	neb::phx::core::actor::rigidactor::base(parent),
	neb::phx::core::actor::rigidstatic::base(parent),
	neb::gfx::core::actor::base(parent),
	neb::fin::gfx_phx::core::actor::base(parent),
	neb::fin::gfx_phx::core::actor::rigidactor::base(parent)
{}
neb::fin::gfx_phx::core::actor::rigidstatic::base::~base() {
	LOG(lg, neb::core::sl, debug) << __PRETTY_FUNCTION__;
}
void						neb::fin::gfx_phx::core::actor::rigidstatic::base::init() {
	neb::core::core::actor::base::init();

	neb::gfx::core::actor::base::init();

	neb::phx::core::actor::base::init();
	//neb::phx::core::actor::actor::base::init();
	//neb::phx::core::actor::rigidactor::base::init();
	//neb::phx::core::actor::rigidstatic::base::init();

	neb::fin::gfx_phx::core::actor::base::init();
	//neb::fin::gfx_phx::core::actor::rigidactor::base::init();
}
void						neb::fin::gfx_phx::core::actor::rigidstatic::base::release() {
	neb::core::core::actor::base::release();
	
	neb::gfx::core::actor::base::release();
	
	//neb::phx::core::actor::base::release();
	neb::phx::core::actor::actor::base::release();
	//neb::phx::core::actor::rigidactor::base::release();
	//neb::phx::core::actor::rigidstatic::base::release();

	neb::fin::gfx_phx::core::actor::base::release();
	//neb::fin::gfx_phx::core::actor::rigidactor::base::release();
}
void						neb::fin::gfx_phx::core::actor::rigidstatic::base::step(gal::etc::timestep const & ts) {
}

