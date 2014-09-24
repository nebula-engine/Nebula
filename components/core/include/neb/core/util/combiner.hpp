#ifndef NEBULA_UTIL_COMBINER_HPP
#define NEBULA_UTIL_COMBINER_HPP

#include <neb/core/util/log.hpp>

namespace neb { namespace util {

	struct combiner {
		typedef int result_type;
		
		template<typename InputIterator> result_type		operator()(InputIterator first, InputIterator last) const
		{
			static const char * func = "combiner::operator()";

			LOG(lg, neb::core::sl, debug) << func;

			result_type f;
			
			while (first != last)
			{
				LOG(lg, neb::core::sl, debug) << func << " first";
				f = *first;
				
				LOG(lg, neb::core::sl, debug) << func << " *first=" << f;
				
				if(f) break;

				LOG(lg, neb::core::sl, debug) << func << " inc";
				++first;
			}

			return 0;
		}
	};

}}

#endif



