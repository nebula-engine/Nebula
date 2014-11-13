#ifndef NEBULA_UTIL_COMBINER_HPP
#define NEBULA_UTIL_COMBINER_HPP

<<<<<<< HEAD
=======
#include <neb/core/util/log.hpp>

>>>>>>> d0f62233eb8fed722542d3bfcc237575d904a507
namespace neb { namespace util {

	struct combiner {
		typedef int result_type;
		
<<<<<<< HEAD
		template<typename InputIterator> result_type		operator()(InputIterator first, InputIterator last) const {
		
			while (first != last) {
				if(*first) break;
=======
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
>>>>>>> d0f62233eb8fed722542d3bfcc237575d904a507
				++first;
			}

			return 0;
		}
	};

}}

#endif



