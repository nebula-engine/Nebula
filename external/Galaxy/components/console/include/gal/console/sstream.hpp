#ifndef NEBULA_UTIL_TERMINAL_STRINGSRTEAM_HPP
#define NEBULA_UTIL_TERMINAL_STRINGSRTEAM_HPP

#include <string>
#include <deque>
#include <sstream>


#include <gal/console/__base.hpp>

namespace gal { namespace console {
	
	/** @brief temporary stringstream */
	struct stringstream {
		stringstream(std::shared_ptr<gal::console::__base> b);
		stringstream(stringstream&& ss);
		~stringstream();
		template<typename T> stringstream		operator<<(T const & t) {
			assert(b_);
			b_->ss_ << t;
			return ::std::move(*this);
		}
		std::shared_ptr<gal::console::__base>		b_;
	};
	
	
}}

#endif
