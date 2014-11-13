#ifndef NEB_GFX_GLSL_ARRAY_HPP
#define NEB_GFX_GLSL_ARRAY_HPP

#include <stdio.h>
#include <tuple>
#include <memory>
#include <iostream>
#include <iomanip>

#include <gal/stl/helper.hpp>

#include <neb/gfx/util/io.hpp>
#include <neb/gfx/util/log.hpp>

#include <neb/gfx/opengl/uniform.hpp>
#include <neb/gfx/glsl/util/decl.hpp>
#include <neb/gfx/util/array_basic.hpp>

namespace neb { namespace gfx {

	template<class... T> class array: public array_basic<T...> {
		public:

			using array_basic<T...>::size_array;

			typedef typename gens<sizeof...(T)>::type	seq_type;

			array():
				_M_closed(0),
				_M_size(0) {}
			
			void				alloc(int n)
			{
				LOG(lg, neb::gfx::sl, debug) << __PRETTY_FUNCTION__ << " " << this;

				assert(_M_closed == 0);

				array_basic<T...>::alloc(n);
				
				_M_closed = new int[n];
				
				for(int i = 0; i < n; i++) {
					_M_closed[i] = 0;
				}

				_M_size = 0;
			}
			int				reg_array(T... initial)
			{
				LOG(lg, neb::gfx::sl, debug) << __PRETTY_FUNCTION__ << " " << this;

				if(_M_closed == 0) abort();
			
			
				// search for empty slot
				int i = 0;
				while(_M_closed[i]) i++;
				
				// mark slot as filled
				_M_closed[i] = 1;

				// update size
				if((i + 1) > _M_size) _M_size = i + 1;

				// initial values
				array_basic<T...>::set(i, initial...);

				LOG(lg, neb::gfx::sl, debug) << __PRETTY_FUNCTION__ << " " << this << " i=" << i << " size=" << _M_size;

				// return position to object so it can access it later
				return i;
			}
			void					unreg_array(int i)
			{
				LOG(lg, neb::gfx::sl, debug) << __PRETTY_FUNCTION__ << " " << this;

				_M_closed[i] = 0;

				if((i+1) == _M_size) {
					while(isOpen(_M_size - 1)) _M_size--;
				}
			}
			template<int I, typename U> void	set_array(int i, U const & u) {
				array_basic<T...>::template set<I>(i,u);
			}
			bool					isClosed(int i) const
			{
				assert(i < size_array());
				return (_M_closed[i] == 1);
			}
			bool					isOpen(int i) const
			{
				assert(i < size_array());
				return (_M_closed[i] == 0);
			}
			GLsizei					size() const
			{
				return _M_size;
			}
			int const * const			getClosed() const
			{
				return _M_closed;
			}
		private:
			int*					_M_closed;
			GLsizei					_M_size;
	};
}}

#endif
