#ifndef NEBULA_UTIL_PARENT_HH
#define NEBULA_UTIL_PARENT_HH

#include <Nebula/Types.hh>
#include <Nebula/Util/Map.hh>
#include <Nebula/Util/WrapperTyped.hh>

namespace Neb {
	namespace Util {
		template<class T> class Parent {
			public:
				typedef T				__type_type;
				typedef std::shared_ptr<T>		__shared_type;
				typedef Neb::WrapperTyped<T>		__wrapper_type;
				typedef typename Neb::Map<T>		map_type;

				Parent();

				void					insert(__shared_type s);
				void					insert(__shared_type s, int i);

				__shared_type				get(Neb::Util::index_type i) {
					auto it = map_.find(i);

					if(it == map_.end()) return __shared_type();

					return it->second.ptr_;
				}

				void					release(Neb::Util::index_type i) {
					auto it = map_.find(i);

					assert(it != map_.end());

					it->second.ptr_->release();

					map_.erase(it);
				}
				void					clear() {
					map_.for_each([] (typename std::map<int, __wrapper_type>::const_iterator it) {
							it->second.ptr_->release();
							});

					map_.clear();
				}



				map_type				map_;
		};
	}
}

#endif




