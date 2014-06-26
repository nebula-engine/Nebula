#ifndef NEBULA_UTIL_COMBINER_HPP
#define NEBULA_UTIL_COMBINER_HPP

namespace neb { namespace util {

	struct combiner {
		typedef int result_type;
		
		template<typename InputIterator> result_type		operator()(InputIterator first, InputIterator last) const {
		
			while (first != last) {
				if(*first) break;
				++first;
			}

			return 0;
		}
	};

}}

#endif



