#ifndef GAL_CHILD_HPP
#define GAL_CHILD_HPP

#include <cstdlib>
#include <cassert>

namespace gal { namespace stl {

	template<typename T> class child {
		public:
			typedef T parent_t;

			/**
			 * exists so you don't have to call every construct for every class in a virtual class hierarchy
			 */
			child(): _M_parent(0)
		{
		}


			child(T* p): _M_parent(p)
		{
			assert(p);
		}

			void		setParent(T * const & p)
			{
				assert(p);
				
				assert(dynamic_cast<gal::stl::child<T>*>(p) != this);
				
				_M_parent = p;
			}
			T* const &	getParent() const
			{
				assert(_M_parent);
				return _M_parent;
			}
			bool		hasParent() const
			{
				return _M_parent != NULL;
			}
		private:
			T*	_M_parent;
	};

}}

#endif

