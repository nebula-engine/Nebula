#ifndef __JESS_MAP_HPP__
#define __JESS_MAP_HPP__

#include <map>
#include <assert.h>
#include <functional>
#include <stdio.h>

#include <boost/serialization/map.hpp>

#include <Nebula/Util/WrapperTyped.hh>

namespace Neb {
	template <class T> class Map {
		public:
			typedef int							__index_type;
			typedef std::shared_ptr<T>					shared_type;
			
			typedef Neb::WrapperTyped<T>					mapped_type;

			typedef std::weak_ptr< Neb::Factory<T> >			factory_weak;
			
			typedef std::map<__index_type,mapped_type>			__map_type;
			typedef typename __map_type::iterator				__iter;			
			typedef typename __map_type::const_iterator			__citer;			


			typedef typename __map_type::iterator			iterator;
			typedef typename __map_type::value_type			value_type_const;
			typedef std::pair<__index_type,mapped_type>		value_type;
			
			/** @brief Constructor */
			Map(factory_weak factory): factory_(factory), next_(0) {}
			/*void		add(value_type& p) {
			  p.first = next_++;
			  map_.insert(p);
			  }*/
			/** */
			template<class Archive> void	serialize(Archive & ar, unsigned int const & version) {
				ar & boost::serialization::make_nvp("map",map_);
			}
			void				push_back(shared_type& u) {
				assert(u);
				
				u->i(next_);
				
				mapped_type m(factory_, u);

				map_.emplace(next_, m);

				next_++;
			}
			/** */
			iterator			find(__index_type i) {
				auto it = map_.find(i);
				return it;
			}
			/** */
			void				clear() {
				map_.clear();
			}
			/** */
			iterator			begin() {
				return map_.begin();
			}
			/** */
			iterator			end() {
				return map_.end();
			}
			/** */
			iterator			erase(iterator it) {
				it = map_.erase(it);
				return it;
			}
			//private:
			factory_weak			factory_;
			__index_type			next_;
			__map_type			map_;

	};	
}

#endif





