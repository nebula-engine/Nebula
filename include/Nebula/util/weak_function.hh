#ifndef NEBULA_UTIL_WEAK_FUNCTION_HPP
#define NEBULA_UTIL_WEAK_FUNCTION_HPP

#include <boost/signals2.hpp>

namespace neb {
	template<class T, class R, class... A> class weak_function {
		public:
			typedef R(T::*funcptr)(A...);
			
			typedef boost::signals2::signal<R(A...)> signal_type;
			
			weak_function(funcptr func): func_(func) {}
			
			R func(A... args) {
				auto s = weak_.lock();
				if(s) {
					return (s.*func_)(args...);
				} else {
					connection_.disconnect();
					return R();
				}
			}
			


			funcptr				func_;

			boost::weak_ptr<T>		weak_;

			boost::signals2::connection	connection_;

	};
}

#endif


