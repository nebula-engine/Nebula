#ifndef NEBULA_CORE_SERIALIZATION_HPP
#define NEBULA_CORE_SERIALIZATION_HPP

#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/polymorphic_iarchive.hpp>
#include <boost/archive/polymorphic_oarchive.hpp>

namespace ba = boost::archive;

namespace neb {
	class serializable
	{
		public:
			virtual void	load(ba::naked_xml_iarchive & ar, unsigned int const &) {}
			virtual void	save(ba::naked_xml_oarchive & ar, unsigned int const &) const {}
		//	virtual void	load(ba::xml_iarchive & ar, unsigned int const &) {}
		//	virtual void	save(ba::xml_oarchive & ar, unsigned int const &) const {}
			virtual void	load(ba::binary_iarchive & ar, unsigned int const &) {}
			virtual void	save(ba::binary_oarchive & ar, unsigned int const &) const {}

			virtual void	load(ba::polymorphic_iarchive & ar, unsigned int const &) = 0;
			virtual void	save(ba::polymorphic_oarchive & ar, unsigned int const &) const = 0;

			BOOST_SERIALIZATION_SPLIT_MEMBER();
	};
}

#endif
