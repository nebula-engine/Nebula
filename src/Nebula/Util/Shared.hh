#ifndef __GRU_SHARED_HPP__
#define __GRU_SHARED_HPP__

#include <boost/enable_shared_from_this.hpp>

namespace Neb {
	namespace Util {
		/** @brief %Shared.
		 * avoid multiple enabled_shared_from_this bases
		 */
		class Shared:
			virtual public std::enable_shared_from_this<Shared>
		{
			public:
				virtual ~Shared() {}
		};
	}
}

#endif

