#ifndef __JESS_MAP_HPP__
#define __JESS_MAP_HPP__

#include <map>
#include <assert.h>
#include <functional>
#include <stdio.h>

#include <Nebula/Memory/smart_ptr.hpp>

//#include <galaxy/except.hpp>

namespace Neb {
	template <class T> class Map {
		public:
			typedef std::shared_ptr<T>			mapped_type;
			typedef std::weak_ptr<T>			weak_type;

			typedef std::map<int,mapped_type>		map_type;
			typedef typename map_type::iterator		iter;
			typedef typename map_type::value_type		value_type_const;
			typedef std::pair<int,mapped_type>		value_type;
			/** @brief Constructor */
			Map():next_(0) {}
			/** @brief Array Subscript */
			weak_type& operator[](const int& k) {
				return map_[k];
			}
			
			/*void		add(value_type& p) {
				p.first = next_++;
				map_.insert(p);
			}*/
			void		push_back(mapped_type& u) {
				//printf("%s\n", __PRETTY_FUNCTION__);
				
				assert(u);
				
				u->i(next_);
				
				//value_type p;

				//p.first = next_;
				//p.second.swap(u);
				
				map_.emplace(next_, std::move(u));
				
				//map_.insert(p);

				next_++;
			}
			iter find(int a) {
				auto it = map_.find( a );

				return it;
			}
			//template <class U> void foreach(std::function<void(U*)> func)
			template <class U> void foreach(std::function<void(Neb::weak_ptr<U>)> func)
			{
				assert(func);
				
				weak_type u;
				for(auto it = map_.begin(); it != map_.end(); ++it) {
					u = Neb::dynamic_pointer_cast<T,U>(it->second);

					if(u) {
						//func(u.get());
						func(u);
					} else {
						throw;// gal::except("null pointer");
					}
				}
			}
			void clear()
			{
				map_.clear();
			}
			iter begin()
			{
				return map_.begin();
			}
			iter end()
			{
				return map_.end();
			}
			iter erase(iter it)
			{
				it = map_.erase(it);
				return it;
			}
			//private:
			map_type	map_;
			int		next_;
	};	
}

#endif





