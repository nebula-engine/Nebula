#ifndef NEBULA_UTIL_SHARED_HPP__
#define NEBULA_UTIL_SHARED_HPP__

/** @file shared.hpp
 */

#include <Nebula/Util/shared.hpp>

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
				virtual void					step(Neb::Core::TimeStep const & ts);

		};
	}
}

#endif




