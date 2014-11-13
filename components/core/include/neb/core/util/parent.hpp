#ifndef NEBULA_UTIL_PARENT_HPP
#define NEBULA_UTIL_PARENT_HPP

<<<<<<< HEAD
#include <gal/stl/parent.hpp>
=======
#include <iostream>

#include <gal/stl/parent.hpp>
#include <gal/stl/deleter.hpp>
>>>>>>> d0f62233eb8fed722542d3bfcc237575d904a507
#include <gal/etc/timestep.hpp>

#include <neb/core/itf/shared.hpp>

namespace neb {
	namespace util {
<<<<<<< HEAD
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

=======
		template<typename CHILD, typename PARENT> class parent:
			virtual public gal::stl::parent<CHILD>
		{
			public:
				typedef gal::stl::parent<CHILD>						gal_parent;
				typedef typename gal::stl::parent<CHILD>::map_type			map_type;
				typedef typename map_type::iterator					iterator;
				typedef typename map_type::pointer					pointer;
				typedef std::shared_ptr<CHILD>	shared;
				typedef std::weak_ptr<CHILD>	weak;
				
				// create
				template<typename U> std::weak_ptr<U>				create()
				{
					std::shared_ptr<U> u(new U, gal::stl::deleter<U>());
					
					gal_parent::insert(u);

					u->init(dynamic_cast<PARENT*>(this));

					return u;
				}
				// insert
				void								insert(shared t)
				{
					gal_parent::insert(t);
					t->init(dynamic_cast<PARENT*>(this));
				}




				template<typename... A> void		init(A... a)
				{
					for(auto it = gal_parent::map_.begin(); it != gal_parent::map_.end(); ++it)
					{
						auto p = it->second.ptr_;
						assert(p);
						p->init(a...);
					}
				}
			
			
				void		step(gal::etc::timestep const & ts)
				{
					//std::cout << __PRETTY_FUNCTION__ << std::endl;
					gal_parent::map_.for_each([&] (pointer p) {
							p->step(ts);
							});
>>>>>>> d0f62233eb8fed722542d3bfcc237575d904a507
				}

		};
	}
}

#endif
