#ifndef __JESS_ASIO_ARCHIVE_HPP
#define __JESS_ASIO_ARCHIVE_HPP

#include <sstream>

namespace gal {
	namespace net {
		class iarchive {
			public:
				iarchive(::std::stringstream& ss): ss_(ss) {
				}
				::std::stringstream &		ss_;
		};
		class oarchive {
			public:
				oarchive(::std::stringstream & ss): ss_(ss) {
				}
				oarchive&			operator<<(::std::string str) {
					ss_ << str;
					return *this;
				}
				::std::stringstream &		ss_;
		};
	}
}

#endif
