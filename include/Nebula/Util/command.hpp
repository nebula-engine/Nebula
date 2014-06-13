#ifndef NEBULA_UTIL_COMMAND_HPP
#define NEBULA_UTIL_COMMAND_HPP

#include <boost/program_options.hpp>

namespace bpo = boost::program_options;


#include <Nebula/Types.hh>
#include <Nebula/Util/typedef.hpp>

namespace neb { namespace util {


	class command {
		public:
			typedef sp::shared_ptr<neb::util::terminal>		terminal_type;

			void		operator()(terminal_type term, int ac, char const ** av) {
				bpo::variables_map vm;
				bpo::store(bpo::parse_command_line(ac, av, desc_), vm);
				bpo::notify(vm);
				if(func_) {
					func_(term, vm);
				}
			}

			bpo::options_description						desc_;

			::std::function<void(terminal_type term, bpo::variables_map)>		func_;
	};



}}

#endif
