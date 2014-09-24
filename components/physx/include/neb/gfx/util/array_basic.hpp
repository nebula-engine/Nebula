#ifndef NEB_GFX_GLSL_ARRAY_BASIC_HPP
#define NEB_GFX_GLSL_ARRAY_BASIC_HPP

#include <stdio.h>
#include <tuple>
#include <memory>
#include <iostream>
#include <iomanip>

#include <gal/stl/helper.hpp>

namespace neb { namespace gfx {
	template<class... T> class array_basic {
		public:
			typedef typename gens<sizeof...(T)>::type	seq_type;
		
			array_basic(): size_array_(0) {}

			/** allocate memory */
			void						alloc(size_t n)
			{
				assert(n > 0);
				size_array_ = n;
				alloc(seq_type(), n);
			}
			/** set all values at index */
			void						set(int i, T... value) {
				set(seq_type(), i, value...);
			}
			/** set value for collection I at index i */
			template<int I, typename U> void		set(int i, U const & u) {
				std::get<I>(data_)[i] = u;
			}
			template<int I, typename U> U* const &		get() {
				return std::get<I>(data_);
			}
			template<int I, typename U> U const &		get(int i) {
				return std::get<I>(data_)[i];
			}
			size_t						size_array() const
			{
				return size_array_;
			}
		private:
			template<int... S> void				alloc(seq<S...>, int n) {
				pass((std::get<S>(data_) = new T[n])...);
			}
			template<int... S> void				set(seq<S...>, int i, T... value) {
				pass((std::get<S>(data_)[i] = value)...);
			}
			
			// collection of data arrays
			std::tuple<T*...>			data_;
			size_t					size_array_;
	};
}}

#endif

