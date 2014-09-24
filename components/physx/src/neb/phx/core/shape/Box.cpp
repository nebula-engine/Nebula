
<<<<<<< HEAD
#include <neb/phx/util/convert.hpp>
#include <neb/phx/core/shape/box.hpp>
#include <neb/phx/core/actor/rigidactor/base.hpp>

neb::phx::core::shape::box::box(std::shared_ptr<neb::phx::core::shape::util::parent> parent):
	neb::core::core::shape::base(parent),
	neb::phx::core::shape::base(parent)
{
}
physx::PxGeometry*		neb::phx::core::shape::box::to_geo() {
	return new physx::PxBoxGeometry(neb::phx::util::convert(s_ * 0.5f));
=======
#include <neb/phx/core/shape/box.hpp>
#include <neb/phx/core/actor/rigidactor/base.hpp>

neb::phx::core::shape::box::box()
{
}
void				neb::phx::core::shape::box::init(neb::core::core::shape::util::parent * const & p)
{
	std::cout << __PRETTY_FUNCTION__ << std::endl;

	create_physics();
}
physx::PxGeometry*		neb::phx::core::shape::box::to_geo() {
	return new physx::PxBoxGeometry(
			scale_[0] * 0.5f,
			scale_[1] * 0.5f,
			scale_[2] * 0.5f
			);
>>>>>>> d0f62233eb8fed722542d3bfcc237575d904a507
}



