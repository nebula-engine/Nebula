#ifndef __JESS_MAP_HPP__
#define __JESS_MAP_HPP__

#include <map>
#include <assert.h>
#include <functional>
#include <stdio.h>

#include <boost/thread.hpp>

#include <boost/serialization/map.hpp>

#include <Nebula/Util/WrapperTyped.hh>

namespace Neb {
	template <class T> class Map {
		public:
			typedef std::shared_ptr<T>					shared_type;
			
			typedef Neb::WrapperTyped<T>					mapped_type;

			typedef std::weak_ptr< Neb::Factory<T> >			factory_weak;
			
			typedef std::map<Neb::Util::index_type,mapped_type>		map_type;

			typedef typename map_type::iterator				iterator;
			typedef typename map_type::const_iterator			const_iterator;

			typedef typename map_type::value_type				value_type_const;
			typedef std::pair<Neb::Util::index_type, mapped_type>		value_type;
			
			enum { CONTINUE, BREAK };

			/** @brief Constructor */
			Map() {}
			Map(factory_weak factory): factory_(factory) {}
			/*void		add(value_type& p) {
			  p.first = next_++;
			  map_.insert(p);
			  }*/
			/** */
			template<class Archive> void	serialize(Archive & ar, unsigned int const & version) {
				boost::lock_guard<boost::mutex> lk(mutex_);
				
				ar & boost::serialization::make_nvp("map",map_);
			}
			void				push_back(shared_type& u) {
				boost::lock_guard<boost::mutex> lk(mutex_);
				
				assert(u);
				
				mapped_type m(u);
				
				map_.emplace(u->i_, m);
			}
			void				for_each(std::function<void(const_iterator)> const & f) {
				boost::lock_guard<boost::mutex> lk(mutex_);

				for(auto it = map_.cbegin(); it != map_.cend(); ++it) {
					f(it);
				}
			}
			void				for_each_int(std::function<int(const_iterator)> const & f) {
				boost::lock_guard<boost::mutex> lk(mutex_);
				
				int ret;
				
				for(auto it = map_.cbegin(); it != map_.cend(); ++it) {
					ret = f(it);
					if(ret == CONTINUE) {
						continue;
					} else {
						break;
					}
				}
			}
			/** */
			shared_type			find(Neb::Util::index_type i) {
				boost::lock_guard<boost::mutex> lk(mutex_);
				
				auto it = map_.find(i);
				return it->second.ptr_;
			}
			/** */
			void				clear() {
				boost::lock_guard<boost::mutex> lk(mutex_);
				
				for(auto it = map_.cbegin(); it != map_.cend(); ++it) {
					it->second.ptr_->release();
				}
				
				map_.clear();
			}
			/** */
			void				release(Neb::Util::index_type i) {
				boost::lock_guard<boost::mutex> lk(mutex_);
				
				auto it = map_.find(i);
				
				if(it == map_.cend()) return;
				
				it->second.ptr_->release();
				
				map_.erase(it);
			}
		private:
			factory_weak			factory_;
			map_type			map_;
			boost::mutex			mutex_;
	};	
}

#endif





