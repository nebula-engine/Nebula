#ifndef NEBULA_MEMORY_GREEDY_PTR_HPP
#define NEBULA_MEMORY_GREEDY_PTR_HPP

#include <cassert>

#include <boost/weak_ptr.hpp>
#include <boost/shared_ptr.hpp>

namespace Neb {
	template<class T> class unique_ptr;

	template<class T> class weak_ptr {
		public:
			friend class unique_ptr<T>;
			weak_ptr() {}
			weak_ptr(Neb::weak_ptr<T> const & ptr): ptr_(ptr.ptr_) {}
			weak_ptr(boost::shared_ptr<T> const & ptr): ptr_(ptr) {}
			//weak_ptr(boost::weak_ptr<T> ptr): ptr_(ptr) {}
			

			operator bool() {
				return bool(!ptr_.expired());
			}
			operator boost::weak_ptr<T>() {
				return boost::weak_ptr<T>(ptr_);
			}
			boost::shared_ptr<T>			operator->() {
				auto ptr = ptr_.lock();
				assert(ptr);
				return ptr;
			}
			boost::shared_ptr<T>			lock() {
				auto ptr = ptr_.lock();
				return ptr;
			}
			boost::shared_ptr<T> const		operator->() const {
				auto ptr = ptr_.lock();
				assert(ptr);
				return ptr;
			}
		//private:
			boost::weak_ptr<T>	ptr_;
	};
	template<class T> class unique_ptr {
		public:
			unique_ptr(T* t = NULL): ptr_(t) {}
			unique_ptr(unique_ptr const && ptr): ptr_(std::move(ptr.ptr_)) {}
			~unique_ptr() {}
		private:
			unique_ptr(unique_ptr<T> const &) {}
			unique_ptr<T>&		operator=(unique_ptr<T> const &) {}
		public:
			void			swap(Neb::unique_ptr<T>& ptr) {
				ptr_.swap(ptr.ptr_);
			}
			void			reset(T* t = NULL) {
				ptr_.reset(t);
			}
			boost::shared_ptr<T>	operator->() {
				return ptr_;
			}
			T &			operator*() {
				return *ptr_;
			}
			T const &		operator*() const {
				return *ptr_;
			}
			boost::shared_ptr<T> const & operator->() const {
				return ptr_;
			}
			operator bool() {
				return bool(ptr_);
			}
			operator boost::weak_ptr<T>() {
				return boost::weak_ptr<T>(ptr_);
			}
			operator Neb::weak_ptr<T>() {
				Neb::weak_ptr<T> p;
				p.ptr_ = ptr_;
				return p;
			}
			operator Neb::weak_ptr<T>() const {
				Neb::weak_ptr<T> p;
				p.ptr_ = ptr_;
				return p;
			}
		private:
			boost::shared_ptr<T>	ptr_;
	};
	template<class From,class To> Neb::weak_ptr<To>	dynamic_pointer_cast(Neb::weak_ptr<From> ptr) {
		Neb::weak_ptr<To> ret;
		ret.ptr_ = boost::dynamic_pointer_cast<To>(ptr.ptr_);
	}
}

#endif



