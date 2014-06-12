#include <iomanip>

#include <Galaxy-Log/log.hpp>

#include <Nebula/Math/geo/polygon.hpp>
#include <Nebula/Math/Serialization/GLM.hpp>


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
	BOOST_LOG_CHANNEL_SEV(lg, "neb gfx", (severity_level)sl)
		<< std::setw(8) << " "
		<< std::setw(8) << "p"
		<< std::setw(8) << p[0]
		<< std::setw(8) << p[1]
		<< std::setw(8) << p[2];

}


