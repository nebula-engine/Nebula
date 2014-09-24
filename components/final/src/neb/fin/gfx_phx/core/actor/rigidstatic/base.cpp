#include <gal/log/log.hpp>

#include <neb/core/util/log.hpp>

#include <neb/fin/gfx_phx/core/actor/rigidstatic/base.hpp>

<<<<<<< HEAD
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
=======
neb::fin::gfx_phx::core::actor::rigidstatic::base::base()
{}
neb::fin::gfx_phx::core::actor::rigidstatic::base::~base()
{
	LOG(lg, neb::core::sl, debug) << __PRETTY_FUNCTION__;
}
void						neb::fin::gfx_phx::core::actor::rigidstatic::base::init(parent_t * const & p)
{
	LOG(lg, neb::core::sl, debug) << __PRETTY_FUNCTION__;

	setParent(p);

	neb::core::core::actor::base::init(p);

	//neb::gfx::core::actor::base::init(p);

	neb::phx::core::actor::base::init(p);
>>>>>>> d0f62233eb8fed722542d3bfcc237575d904a507
	//neb::phx::core::actor::actor::base::init();
	//neb::phx::core::actor::rigidactor::base::init();
	//neb::phx::core::actor::rigidstatic::base::init();

<<<<<<< HEAD
	neb::fin::gfx_phx::core::actor::base::init();
	//neb::fin::gfx_phx::core::actor::rigidactor::base::init();
}
void						neb::fin::gfx_phx::core::actor::rigidstatic::base::release() {
=======
	neb::fin::gfx_phx::core::actor::base::init(p);
	//neb::fin::gfx_phx::core::actor::rigidactor::base::init();
}
void						neb::fin::gfx_phx::core::actor::rigidstatic::base::release()
{
	LOG(lg, neb::core::sl, debug) << __PRETTY_FUNCTION__;

>>>>>>> d0f62233eb8fed722542d3bfcc237575d904a507
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

