#ifndef __GRU_SHARED_HPP__
#define __GRU_SHARED_HPP__

#include <boost/enable_shared_from_this.hpp>

namespace gru {
	/** @brief %Shared
	 * avoid multiple enabled_shared_from_this bases
	 */
	class shared: virtual public boost::enable_shared_from_this<shared> {
		public:
		virtual ~shared() {}
	};
}

#endif

