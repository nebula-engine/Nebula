#ifndef __JESS_MAP_HPP__
#define __JESS_MAP_HPP__

#include <map>
#include <assert.h>
#include <functional>
#include <stdio.h>

#include <boost/shared_ptr.hpp>

//#include <galaxy/except.hpp>

namespace Neb {
	template <class T> class Map {
		public:
			typedef boost::shared_ptr<T>		mapped_type;
			typedef std::map<int,mapped_type>	map_type;
			typedef typename map_type::iterator	iter;
			
			
			Map():next_(0) {}
			mapped_type& operator[](const int& k) {
				return map_[k];
			}
			template <class U = T> void push_back(mapped_type u) {
				//printf("%s\n", __PRETTY_FUNCTION__);
				
				assert(u);

				u->i(next_);

				map_[next_] = u;

				next_++;
			}
			iter find(int a)
			{
				auto it = map_.find( a );

				return it;
			}
			template <class U> void foreach(std::function<void(U*)> func)
			{
				assert(func);
				
				mapped_type u;
				for(auto it = map_.begin(); it != map_.end(); ++it)
				{
					u = boost::dynamic_pointer_cast<U>(it->second);

					if(u)
					{
						func(u.get());
					}
					else
					{
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





