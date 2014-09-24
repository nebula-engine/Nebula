
#include <neb/core/itf/shared.hpp>

neb::itf::shared::shared() {
	std::cout << __PRETTY_FUNCTION__ << std::endl;
}
void					neb::itf::shared::release() {
	std::cout << __PRETTY_FUNCTION__ << std::endl;
}
/*void					neb::itf::shared::step(gal::etc::timestep const & ts) {
	std::cout << __PRETTY_FUNCTION__ << std::endl;
}*/

