#ifndef NEBULA_UTIL_SHARED_HPP__
#define NEBULA_UTIL_SHARED_HPP__

/** @file shared.hpp
 */

#include <boost/archive/polymorphic_iarchive.hpp>
#include <boost/archive/polymorphic_oarchive.hpp>

#include <gal/itf/shared.hpp>
#include <gal/etc/timestep.hpp>

namespace neb {
	namespace itf {
		/** @brief %shared.
		 *
		 * Avoid multiple enabled_shared_from_this bases.
		 * Provide common base for working with factory and map.
		 * Supply type info.
		 *
		 */
		class shared: virtual public gal::itf::shared {
			public:
				shared();
				/** @brief destructor
				 *
				 */
				virtual ~shared() {}
				virtual void					init();
				virtual void					release();
				virtual void					step(gal::etc::timestep const & ts);

				virtual void					serialize(boost::archive::polymorphic_iarchive & ar, unsigned int const & version);
				virtual void					serialize(boost::archive::polymorphic_oarchive & ar, unsigned int const & version);
		};
	}
}

#endif




