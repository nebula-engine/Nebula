#ifndef NEBULA_UTIL_PARENT_HPP
#define NEBULA_UTIL_PARENT_HPP

#include <gal/stl/parent.hpp>
#include <gal/etc/timestep.hpp>

#include <neb/core/itf/shared.hpp>

namespace neb {
	namespace util {
		template<typename T> class parent: virtual public gal::stl::parent<T> {
			public:
				typedef gal::stl::parent<T>						gal_parent;
				typedef typename gal::stl::parent<T>::map_type				map_type;
				//typedef typename map_type::iterator					itr;
				
				template<int I> using iterator = typename mi::nth_index<typename map_type::container_type, I>::type::iterator;
				
				template<typename U, typename... CtorArgs> std::shared_ptr<U>		cii(CtorArgs... args) {
					auto u(sp::make_shared<U>(args...));
					
					insert(u);
					
					u->init();

					return u;
				}
				void		insert(std::shared_ptr< T > t) {
					gal_parent::insert(t);
				}
				void		init() {
					gal_parent::map_.template for_each<0>([&] (iterator<0> it) {
							it->ptr_->init();
							});

				}
				void		release() {
					gal_parent::map_.template for_each<0>([&] (iterator<0> it) {
							it->ptr_->release();
							});

				}
				void		step(gal::etc::timestep const & ts) {

					gal_parent::map_.template for_each<0>([&] (iterator<0> it) {
							it->ptr_->step(ts);
							});

				}

		};
	}
}

#endif
