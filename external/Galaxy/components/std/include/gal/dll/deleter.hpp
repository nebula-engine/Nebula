#ifndef DLL_DELETER_HPP
#define DLL_DELETER_HPP

#include <dlfcn.h>

#include <memory>
#include <cassert>
#include <string>

#include <gal/itf/typedef.hpp>

#include <gal/dll/helper_info.hpp>

#include <boost/serialization/nvp.hpp>

namespace gal { namespace itf {
	class shared;
}}

namespace gal { namespace dll {

	class helper_base;

	struct deleter
	{
		public:
			helper_info const	getHelperInfo();

		public:
			deleter(std::shared_ptr<helper_base> h, helper_info hi);
			virtual ~deleter();
			deleter(deleter&& d);
			deleter(deleter const & d);

			void			operator()(gal::itf::shared* p);
		private:
			std::shared_ptr<helper_base>		_M_helper;
			helper_info const	hi_;
	};
}}

#endif

