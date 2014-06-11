#ifndef NEBULA_UTIL_COMMAND_HPP
#define NEBULA_UTIL_COMMAND_HPP

#include <boost/program_options.hpp>
namespace bpo = boost::program_options;

namespace neb {
	namespace util {
		class command {
			public:
				void		operator()(sp::shared_ptr<Neb::Graphics::GUI::Object::terminal> term, int ac, char const ** av) {
					bpo::variables_map vm;
					bpo::store(bpo::parse_command_line(ac, av, desc_), vm);
					bpo::notify(vm);
					if(func_) {
						func_(term, vm);
					}
				}
				bpo::options_description	desc_;

				::std::function<void(sp::shared_ptr<Neb::Graphics::GUI::Object::terminal> term, bpo::variables_map)>		func_;
		};
	}
}

#endif
