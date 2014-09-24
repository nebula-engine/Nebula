#ifndef NEB_GFX_GLSL_ARRAY_BASIC_DOUBLE_BUFFERED_HPP
#define NEB_GFX_GLSL_ARRAY_BASIC_DOUBLE_BUFFERED_HPP

#include <stdio.h>
#include <tuple>
#include <memory>
#include <iostream>
#include <iomanip>
#include <exception>

#include <gal/stl/helper.hpp>

#include <neb/gfx/opengl/uniform.hpp>
#include <neb/gfx/util/io.hpp>
#include <neb/gfx/glsl/util/decl.hpp>



namespace neb { namespace gfx {
	template<class... T> class array_basic_double_buffered {
		public:
			typedef typename gens<sizeof...(T)>::type	seq_type;

			struct capacity: std::exception {
				const char * what() const {
					return "capacity reached";
				}
			};

			array_basic_double_buffered():
				front_(data_),
				back_(data_ + 1),
				size_(0),
				size_array_(0)	{}
			
			void					alloc(int n)
			{
				LOG(lg, neb::gfx::sl, debug) << __PRETTY_FUNCTION__ << " " << this;

				assert(n > 0);

				assert(size_array_ == 0);

				size_array_ = n;
				alloc(seq_type(), n);
			}
		private:
			template<int... S> void			alloc(seq<S...>, int n)
			{
				pass((std::get<S>(*front_) = new T[n])...);
				pass((std::get<S>(*back_) = new T[n])...);
			}
		public:
			void					set(int i, T... value) {
				assert(size_array_ > 0);

				set(seq_type(), i, value...);
			}
			template<int I, typename U> void	set(int i, U const & u) {
				std::get<I>(*front_)[i] = u;
			}
		private:
			template<int... S> void			set(seq<S...>, int i, T... value) {
				pass((std::get<S>(*front_)[i] = value)...);
			}
		public:
			void					swap_buffers() {
				std::swap(front_, back_);
			}
			void					copy_data(GLsizei oldi, GLsizei newi) {
				copy_data(seq_type(), oldi, newi);
			}
			template<int... S> void			copy_data(seq<S...>, GLsizei oldi, GLsizei newi) {
				pass(copy_data__<S>(oldi, newi)...);
			}
			template<int I> int			copy_data__(GLsizei oldi, GLsizei newi) {
				std::get<I>(*back_)[newi] = std::get<I>(*front_)[oldi];
				return 0;
			}
			void					set_size(GLsizei s) {
				LOG(lg, neb::gfx::sl, debug) << __PRETTY_FUNCTION__ << " " << this << " size = " << s;
				size_ = s;
			}
			template<int I, typename U> U*		get() {
				return std::get<I>(*front_);
			}
			int					next()
			{
				LOG(lg, neb::gfx::sl, debug) << __PRETTY_FUNCTION__ << " " << this << " size = " << size_+1;
				if(size_ == size_array_) throw 0;
				GLsizei s = size_;
				size_++;
				return s;
			}
			GLsizei					size() const {
				return size_;
			}
			GLsizei					size_array() const {
				return size_array_;
			}

		private:
			std::tuple<T*...>			data_[2];
			std::tuple<T*...>*			front_;
			std::tuple<T*...>*			back_;

			GLsizei					size_;
			GLsizei					size_array_;
	};
}}

#endif
