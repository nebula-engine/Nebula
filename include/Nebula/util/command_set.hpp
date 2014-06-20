#ifndef NEBULA_UTIL_COMMAND_SET_HPP
#define NEBULA_UTIL_COMMAND_SET_HPP

#include <map>
#include <string>

#include <Nebula/util/decl.hpp>
#include <Nebula/util/typedef.hpp>

namespace neb { namespace util {

	/** @brief %command_set */
	struct command_set {

		typedef ::std::map< ::std::string, sp::shared_ptr<neb::util::command> >		map_type;

		void			init();
		void			list_commands(sp::shared_ptr<neb::util::terminal> term);
		void			operator()(sp::shared_ptr<neb::util::terminal> term, ::std::string str);

		map_type		map_;

	};



}}


#endif





