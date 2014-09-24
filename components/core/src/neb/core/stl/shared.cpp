
#include <neb/core/itf/shared.hpp>

neb::itf::shared::shared() {
<<<<<<< HEAD
}
void					neb::itf::shared::init() {
	gal::itf::shared::__init();
}
void					neb::itf::shared::release() {
}
void					neb::itf::shared::step(gal::etc::timestep const & ts) {
}
void					neb::itf::shared::serialize(boost::archive::polymorphic_iarchive & ar, unsigned int const & version) {
}
void					neb::itf::shared::serialize(boost::archive::polymorphic_oarchive & ar, unsigned int const & version) {
}
=======
	std::cout << __PRETTY_FUNCTION__ << std::endl;
}
void					neb::itf::shared::release() {
	std::cout << __PRETTY_FUNCTION__ << std::endl;
}
/*void					neb::itf::shared::step(gal::etc::timestep const & ts) {
	std::cout << __PRETTY_FUNCTION__ << std::endl;
}*/
>>>>>>> d0f62233eb8fed722542d3bfcc237575d904a507

