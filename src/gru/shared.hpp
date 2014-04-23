#ifndef __GRU_SHARED_HPP__
#define __GRU_SHARED_HPP__

#include <memory>

namespace gru {
	/** @brief %Shared
	 * avoid multiple enabled_shared_from_this bases
	 */
	class shared: virtual public std::enable_shared_from_this<shared> {
		public:
		virtual ~shared() {}
	};
}

#endif

