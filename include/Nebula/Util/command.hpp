#ifndef NEBULA_UTIL_COMMAND_HPP
#define NEBULA_UTIL_COMMAND_HPP

#include <boost/program_options.hpp>

namespace neb {
	namespace util {
		class command {
			public:
				void		operator()(int ac, char** av) {

				}
				bpo::options_description	desc_;

				std::function<void(bpo::variables_map)>		func_;
		};
	}
}

#endif
