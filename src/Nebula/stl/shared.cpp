#include <Nebula/util/shared.hpp>

neb::std::shared::shared() {
}
void					neb::std::shared::init() {
	gal::std::shared::init();
}
void					neb::std::shared::release() {
}
void					neb::std::shared::step(neb::core::TimeStep const & ts) {
}
void					neb::std::shared::serialize(boost::archive::polymorphic_iarchive & ar, unsigned int const & version) {
}
void					neb::std::shared::serialize(boost::archive::polymorphic_oarchive & ar, unsigned int const & version) {
}

