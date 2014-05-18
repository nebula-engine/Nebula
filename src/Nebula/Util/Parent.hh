#ifndef NEBULA_UTIL_PARENT_HH
#define NEBULA_UTIL_PARENT_HH

#include <Nebula/Types.hh>
#include <Nebula/Util/Address.hh>
#include <Nebula/Util/Map.hh>
#include <Nebula/Util/WrapperTyped.hh>


namespace Neb {
	namespace Util {
		template<class T> class Parent {
			public:
				typedef T			__type_type;
				typedef std::shared_ptr<T>	__shared_type;
				typedef Neb::WrapperTyped<T>	__wrapper_type;
				typedef Neb::Map<T>		__map_type;
				
				typedef Neb::Util::Address<T>	__address_type;
				typedef Neb::Util::index_type	__index_type;
	
				Parent();

				void					insert(__shared_type s);
				void					insert(__shared_type s, int i);
				
				__shared_type				getActor(__index_type i);
				__shared_type				getActor(__address_type a);
				
				void					releaseActor(__index_type i);
				
				


				__map_type				map_;
		};
	}
}

#endif
