#ifndef NEBULA_UTIL_PARENT_HPP
#define NEBULA_UTIL_PARENT_HPP

#include <Galaxy-Standard/parent.hpp>

#include <Nebula/Core/TimeStep.hpp>

namespace Neb {
	namespace Util {
		template<typename T> class parent: virtual public gal::std::parent<T> {
			public:
				typedef typename gal::std::parent<T>::map_type		map_type;
				//typedef typename map_type::iterator			itr;
				
				template<int I> using iterator = typename mi::nth_index<typename map_type::container_type, I>::type::iterator;
				
				void		init() {
					gal::std::parent<T>::map_.template for_each<0>([&] (iterator<0> it) {
							it->ptr_->init();
							});

				}
				void		release() {
					gal::std::parent<T>::map_.for_each<0>([&] (iterator<0> it) {
							it->ptr_->release();
							});

				}
				void		step(Neb::Core::TimeStep const & ts) {

					gal::std::parent<T>::map_.template for_each<0>([&] (iterator<0> it) {
							it->ptr_->step(ts);
							});

				}

		};
	}
}

#endif
