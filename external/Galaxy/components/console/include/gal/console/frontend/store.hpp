#ifndef GAL_CONSOLE_FRONTEND_STORE_HPP
#define GAL_CONSOLE_FRONTEND_STORE_HPP

#include <deque>
#include <string>

#include <gal/console/base.hpp>

namespace gal { namespace console { namespace frontend {

	class store: virtual public gal::console::base {
		public:
			store();

			virtual void					write_line(::std::string const & s);
			virtual void					enter();

		public:

			unsigned int					lines_max_;

			::std::deque< ::std::string >			lines_;

	};

}}}

#endif
