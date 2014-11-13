#ifndef GAL_LOG_LOG_HPP
#define GAL_LOG_LOG_HPP

#include <cstddef>
#include <iostream>
#include <sstream>
#include <iomanip>

#define LOG(lg, channel, sev) if(sev >= channel) gal::log::base(lg)

enum severity_level {
	debug,
	info,
	warning,
	error,
	critical
};

namespace gal {
	namespace log {
		/** @brief temporary stringstream */
		struct base {
			base(std::ostream& ss);
			base(base&& b);
			~base();
			template<typename T> base&		operator<<(T const & t) {
				ss_ << t;
				//return move(*this);
				return *this;
			}
			std::ostream&				ss_;
		};

		void		init();
		void		refresh();
	}
}

extern std::ostream& lg;

inline std::ostream& operator<< (std::ostream& strm, severity_level level) {
	static const char* strings[] = {
		"debug",
		"info",
		"warning",
		"error",
		"critical"
	};

	if(static_cast<size_t>(level) < sizeof(strings) / sizeof(*strings)) {
		strm << strings[level];
	} else {
		strm << static_cast<int>(level);
	}
	return strm;
}

#endif



