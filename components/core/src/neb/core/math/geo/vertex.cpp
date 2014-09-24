#include <iomanip>

#include <gal/log/log.hpp>

#include <neb/core/util/debug.hpp>
#include <neb/core/math/geo/polygon.hpp>
#include <neb/core/math/Serialization/glm.hpp>
#include <neb/core/util/log.hpp>


void				math::geo::vertex::serialize(boost::archive::polymorphic_iarchive & ar, unsigned int const & version) {
	ar & p;
	ar & n;
	ar & tc;
}
void				math::geo::vertex::serialize(boost::archive::polymorphic_oarchive & ar, unsigned int const & version) {
	ar & p;
	ar & n;
	ar & tc;
}

void		math::geo::vertex::print(int sl) {
	LOG(lg, neb::core::sl, (severity_level)sl)
		<< setw(4) << " "
		<< setw(4) << "p"
		<< setw(8) << p[0]
		<< setw(8) << p[1]
		<< setw(8) << p[2]
		<< setw(4) << "n"
		<< setw(8) << n[0]
		<< setw(8) << n[1]
		<< setw(8) << n[2]
		<< setw(4) << "tcp"
		<< setw(8) << tc[0]
		<< setw(8) << tc[1];
}


