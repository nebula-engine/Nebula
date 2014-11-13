#ifndef HELPER_HPP
#define HELPER_HPP

#include <dlfcn.h>

#include <memory>
#include <cassert>
#include <string>

#include <gal/itf/typedef.hpp>

#include <gal/dll/helper_info.hpp>
#include <gal/dll/deleter.hpp>

#include <boost/serialization/nvp.hpp>

namespace gal { namespace dll {

	class helper_base
	{
		public:
			virtual void		destroy(gal::itf::shared* v) = 0;
	};

	template<class T_, typename... CTOR_ARGS> class helper:
		public std::enable_shared_from_this< helper< T_, CTOR_ARGS... > >,
		public helper_base
	{
		public:
			typedef T_ T;
			typedef std::enable_shared_from_this< helper< T_, CTOR_ARGS... > > estf;
		private:
			helper(helper<T> const & h) {}
		public:
			helper(std::string f, std::string o):
				handle_(0),
				create_(0),
				destroy_(0),
				hi_(f, o, typeid(T)) {}

			helper(helper<T>&& h):
				hi_(h.hi_),
				handle_(std::move(h.handle_)),
				create_(std::move(h.create_)),
				destroy_(std::move(h.destroy_)) {}


			void			open() {

				handle_ = dlopen(hi_.file_name.c_str(), RTLD_LAZY);
				if(handle_ == NULL) {
					perror(dlerror());
					abort();
				}

				auto name_create = hi_.object_name + "_create";
				auto name_destroy = hi_.object_name + "_destroy";

				create_	= (T* (*)(CTOR_ARGS...))dlsym(handle_, name_create.c_str());
				if(create_ == NULL) {
					perror(dlerror());
					abort();
				}

				destroy_ = (void (*)(T*))dlsym(handle_, name_destroy.c_str());
				if(destroy_ == NULL) {
					perror(dlerror());
					abort();
				}
			}
			~helper() {
				if(handle_)
					dlclose(handle_);
			}
		public:
			friend class gal::dll::deleter;

			std::shared_ptr<T>	make_shared(CTOR_ARGS... c)
			{
				std::shared_ptr<T> t(
						create(c...),
						gal::dll::deleter(estf::shared_from_this(), hi_)
						);
				return t;
			}
		private:
			T*		create(CTOR_ARGS... c)
			{
				if(!create_) abort();
				return create_(c...);
			}
			virtual void	destroy(gal::itf::shared* p)
			{
				T* t = dynamic_cast<T*>(p);
				destroy(t);
			}
			void		destroy(T* t)
			{
				if(!destroy_) abort();
				destroy_(t);
			}

		private:
			void*		handle_;
			T*		(*create_)(CTOR_ARGS...);
			void		(*destroy_)(T*);
			helper_info	hi_;
	};
	/*struct deleter
	{
		public:
			helper_info const	getHelperInfo();

		public:
			deleter(std::shared_ptr<helper_base> h, helper_info hi);
			virtual ~deleter();
			deleter(deleter<H>&& d);
			deleter(deleter<H> const & d);

			void			operator()(gal::itf;:shared* p);
		private:
			std::shared_ptr<helper_base>		_M_helper;
			helper_info const	hi_;
	};*/
}}

#endif

