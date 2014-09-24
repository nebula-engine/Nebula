#ifndef __JESS_MAP_HPP__
#define __JESS_MAP_HPP__

#include <map>
#include <assert.h>
#include <functional>
#include <exception>
#include <stdio.h>


#include <boost/multi_index_container.hpp>
#include <boost/multi_index/global_fun.hpp>
#include <boost/multi_index/mem_fun.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/member.hpp>


#include <boost/thread.hpp>

#ifdef GAL_STD_USE_BOOST
#include <boost/serialization/map.hpp>
#endif

#include <gal/stl/wrapper.hpp>

namespace mi = boost::multi_index;

namespace gal {
	namespace stl {
		template <class T, typename... INDICES> class map2 {
			public:
				struct item_not_found: std::exception {
				};
				typedef std::shared_ptr< gal::stl::factory<T> >			factory_shared_type;

				typedef std::shared_ptr<T>					shared_type;

				//typedef gal::stl::wrapper<T>					wrapper_type;

				//typedef ::std::map< gal::itf::index_type, gal::stl::wrapper< T > >		map_type;

				typedef mi::ordered_unique< mi::global_fun<
					gal::stl::wrapper<T> const &,
					gal::itf::index_type const &,
					gal::stl::wrapper<T>::static_get_index > >		index0;

				typedef mi::multi_index_container<
					gal::stl::wrapper<T>,
					mi::indexed_by<index0, INDICES...> >		container_type;

				//typedef mi::nth_index<container_type, 0>::type::iterator	iterator0;

				template<int I> using iterator = typename mi::nth_index<container_type, I>::type::iterator;

				//typedef typename map_type::iterator				iterator;
				//typedef typename map_type::const_iterator			const_iterator;

				//typedef typename map_type::value_type				value_type_const;
				//typedef ::std::pair<gal::itf::index_type, gal::stl::wrapper< T > >		value_type;

				enum { CONTINUE, BREAK };

				/** @brief Constructor */
				map2() {}
				map2(factory_shared_type factory): factory_(factory) {}
				/*void		add(value_type& p) {
				  p.first = next_++;
				  map_.insert(p);
				  }*/
				/** */
				template<class Archive> void		serialize(Archive & ar, unsigned int const & version) {
					boost::lock_guard<boost::mutex> lk(mutex_);

					ar & boost::serialization::make_nvp("container",container_);
				}
				void					insert(std::shared_ptr< T > t) {
					boost::lock_guard<boost::mutex> lk(mutex_);

					assert(t);

					// make sure index is initialized
					auto i = gal::itf::shared::static_get_index(t);
					if(i == -1) {
						//shared_ptr<gal::itf::shared> sh(t);
						t->gal::itf::shared::__init();
					}

					gal::stl::wrapper<T> m(t);

					assert(m.ptr_);

					container_.insert(m);
				}
				template<int I> void			for_each(::std::function<void(iterator<I>)> const & f) {
					boost::lock_guard<boost::mutex> lk(mutex_);

					for(auto it = mi::get<I>(container_).begin(); it != mi::get<I>(container_).cend(); ++it) {
						f(it);
					}
				}
				template<int I> void			for_each_int(::std::function<int(iterator<I>)> const & f) {
					boost::lock_guard<boost::mutex> lk(mutex_);

					int ret;

					for(auto it = mi::get<I>(container_).begin(); it != mi::get<I>(container_).cend(); ++it) {
						ret = f(it);
						if(ret == CONTINUE) {
							continue;
						} else {
							break;
						}
					}
				}
				/** */
				std::shared_ptr<T>			find(gal::itf::index_type i) {
					boost::lock_guard<boost::mutex> lk(mutex_);

					auto it = container_.find(i);
					return it->second.ptr_;
				}
				/** */
				void					clear() {
					boost::lock_guard<boost::mutex> lk(mutex_);

					for(auto it = mi::get<0>(container_).begin(); it != mi::get<0>(container_).cend(); ++it) {
						it->ptr_->release();
					}

					container_.clear();
				}
				/** @brief begin iterator 0
				*/
				shared_type				front() {
					auto it = begin();
					if(it != end()) {
						return it->ptr_;
					}

					return shared_type();
				}
				iterator<0>				begin() {
					return mi::get<0>(container_).begin();
				}
				/** @brief end iterator 0
				*/
				iterator<0>				end() {
					return mi::get<0>(container_).end();
				}
				/** */
				void					erase(gal::itf::index_type i) {

					while(1) {	
						boost::lock_guard<boost::mutex> lk(mutex_);

						auto it = container_.find(i);

						if(it == container_.cend()) return;//throw item_not_found();

						assert(it->ptr_);

						// so deadlock can't occur:
						// if object is already locked, release map then try again
						if(!it->ptr_->mutex_.try_lock()) continue;

						it->ptr_->release();

						it->ptr_->mutex_.unlock();

						container_.erase(it);

						return;
					}
				}
			private:
				factory_shared_type		factory_;
				container_type			container_;
				boost::mutex			mutex_;
		};	

		template <class T> class map {
			public:
				struct item_not_found: std::exception {
				};
				typedef std::shared_ptr< gal::stl::factory<T> >			factory_shared_type;
				typedef std::shared_ptr<T>					pointer;
				typedef gal::stl::wrapper<T>					wrapper_type;


				typedef std::map<gal::itf::index_type, wrapper_type>		container_type;
				typedef typename container_type::value_type			value_type;
				typedef typename container_type::iterator			iterator;

				enum { CONTINUE, BREAK };

				/** @brief Constructor */
				map() {}
				map(factory_shared_type factory): factory_(factory) {}
				/** @brief destructor
				 *
				 * ensure proper shutdown
				 */
				~map()
				{
					assert(container_.empty());
				}
				template<class Archive> void		serialize(Archive & ar, unsigned int const & version) {
					boost::lock_guard<boost::mutex> lk(mutex_);

					ar & boost::serialization::make_nvp("container",container_);
				}
				void					insert(pointer const & t) {
					boost::lock_guard<boost::mutex> lk(mutex_);
					
					auto c = t.use_count(); 

					assert(t);

					// make sure index is initialized
					auto i = gal::itf::shared::static_get_index(t);
					if(i == -1) {
						//shared_ptr<gal::itf::shared> sh(t);
						t->gal::itf::shared::__init();
					}
					
					//gal::stl::wrapper<T> m(t);
	
					//assert(t.use_count() == (c + 1));
				
					std::cout << "t = " << t.get() << std::endl;
					std::cout << "t->_M_index = " << t->_M_index << std::endl;
					
					//container_.insert(value_type(i,m));
		
					auto ret = container_.insert(
							value_type(
								t->_M_index,
								wrapper_type(t)
								)
							);

					if(!ret.second) {					
						std::cout << "not inserted i=" << i << std::endl;
						abort();
					}

					assert(t.use_count() == (c + 1));

				}
				void			for_each(std::function<void(pointer)> const & f) {
					boost::lock_guard<boost::mutex> lk(mutex_);

					for(auto it = container_.begin(); it != container_.cend(); ++it) {
						auto p = it->second.ptr_;
						assert(p);
						f(p);
					}
				}
				void			for_each_int(::std::function<int(pointer)> const & f) {
					boost::lock_guard<boost::mutex> lk(mutex_);

					int ret;

					for(auto it = container_.begin(); it != container_.cend(); ++it) {
						auto p = it->second.ptr_;
						assert(p);
						ret = f(p);
						if(ret == CONTINUE) {
							continue;
						} else {
							break;
						}
					}
				}
				/** */
				std::shared_ptr<T>			find(std::string name)
				{
					boost::lock_guard<boost::mutex> lk(mutex_);

					for(auto it = container_.begin(); it != container_.cend(); ++it)
					{
						auto p = it->second.ptr_;
						assert(p);
						if(p->_M_name == name) return p;
					}

					return std::shared_ptr<T>();
				}
				std::shared_ptr<T>			find(gal::itf::index_type i) {
					boost::lock_guard<boost::mutex> lk(mutex_);
					
					auto it = container_.find(i);
					
					if(it == container_.end()) throw 0;
					
					return it->second.ptr_;
				}
				/** */
				void					clear() {
					std::cout << __PRETTY_FUNCTION__ << std::endl;

					boost::lock_guard<boost::mutex> lk(mutex_);

					// replaced by deleter objects
					//for(auto it = container_.begin(); it != container_.end(); ++it) {
					//	it->second.ptr_->release();
					//}

					container_.clear();
				}
				/** @brief begin iterator 0
				*/
				pointer					front() {
					auto it = begin();
					if(it != end()) {
						return it->second.ptr_;
					}

					return pointer();
				}
				iterator				begin() {
					return container_.begin();
				}
				/** @brief end iterator 0
				*/
				iterator				end() {
					return container_.end();
				}
				/** */
				void					erase(gal::itf::index_type i) {

					while(1) {	
						boost::lock_guard<boost::mutex> lk(mutex_);

						auto it = container_.find(i);

						if(it == container_.cend()) return;//throw item_not_found();

						auto p = it->second.ptr_;

						assert(p);

						// so deadlock can't occur:
						// if object is already locked, release map then try again
						if(!p->mutex_.try_lock()) continue;

						p->release();

						p->mutex_.unlock();

						container_.erase(it);

						return;
					}
				}
				bool				empty() const
				{
					return container_.empty();
				}
			private:
				factory_shared_type		factory_;
				container_type			container_;
				boost::mutex			mutex_;
		};	
	}
}

#endif





