#include <neb/fin/gfx_phx/core/shape/box.hpp>
#include <neb/fin/gfx_phx/core/shape/util/parent.hpp>

neb::fin::gfx_phx::core::shape::box::box(std::shared_ptr<neb::fin::gfx_phx::core::shape::util::parent> parent):
	neb::core::core::shape::base(parent),
	neb::gfx::core::shape::base(parent),
	neb::gfx::core::shape::box(parent),
	neb::phx::core::shape::base(parent),
	neb::phx::core::shape::box(parent),
	neb::fin::gfx_phx::core::shape::base(parent)
{
}
void		neb::fin::gfx_phx::core::shape::box::init() {
	neb::core::core::shape::base::init();

	neb::gfx::core::shape::base::init();
	neb::gfx::core::shape::box::init();

	neb::phx::core::shape::base::init();
	//neb::phx::core::shape::box::init();

	neb::fin::gfx_phx::core::shape::base::init();
}
void		neb::fin::gfx_phx::core::shape::box::release() {
}
void		neb::fin::gfx_phx::core::shape::box::step(gal::etc::timestep const & ts) {
}


