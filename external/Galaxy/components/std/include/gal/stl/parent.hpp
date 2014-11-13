#ifndef GAL_STD_PARENT_HPP
#define GAL_STD_PARENT_HPP

#include <gal/stl/map.hpp>
#include <gal/itf/shared.hpp>
#include <gal/stl/wrapper.hpp>

namespace gal {
	namespace stl {
		template<class T> class parent: virtual public gal::itf::shared {
			public:
				typedef gal::stl::map< T >		map_type;
				parent() {
				}
				void					insert(std::shared_ptr< T > s) {
					map_.insert(s);
				}

				std::shared_ptr< T >			get(gal::itf::index_type i) {
					return map_.find(i);
				}
				void					erase(gal::itf::index_type i) {

					auto me = std::dynamic_pointer_cast< gal::stl::parent< T > >(shared_from_this());
					
					boost::thread t(boost::bind(
							&gal::stl::parent< T >::thread_erase,
							me,
							i
							));
					
					t.detach();
				}
			private:
				void					thread_erase(gal::itf::index_type i) {
					map_.erase(i);
				}
			public:
				void					clear() {
					map_.clear();
				}

			
				map_type				map_;
		};
	}
}

#endif




