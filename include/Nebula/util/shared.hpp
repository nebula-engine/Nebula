#ifndef NEBULA_UTIL_SHARED_HPP__
#define NEBULA_UTIL_SHARED_HPP__

/** @file shared.hpp
 */

#include <boost/archive/polymorphic_iarchive.hpp>
#include <boost/archive/polymorphic_oarchive.hpp>

#include <Galaxy-Standard/shared.hpp>

#include <Nebula/core/TimeStep.hpp>

namespace neb {
	namespace std {
		/** @brief %shared.
		 *
		 * Avoid multiple enabled_shared_from_this bases.
		 * Provide common base for working with factory and map.
		 * Supply type info.
		 *
		 */
		class shared: virtual public gal::std::shared {
			public:
				shared();
				/** @brief Destructor */
				virtual ~shared() {}
				virtual void					init();
				virtual void					release();
				virtual void					step(neb::core::TimeStep const & ts);
				
				virtual void					serialize(boost::archive::polymorphic_iarchive & ar, unsigned int const & version);
				virtual void					serialize(boost::archive::polymorphic_oarchive & ar, unsigned int const & version);
		};
	}
}

#endif




