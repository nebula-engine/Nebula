
#include <neb/core/itf/shared.hpp>

neb::itf::shared::shared() {
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

