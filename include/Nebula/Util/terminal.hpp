#ifndef NEBULA_UTIL_TERMINAL_HPP
#define NEBULA_UTIL_TERMINAL_HPP

#include <string>
#include <deque>

#include <Nebula/Types.hh>
#include <Nebula/Util/typedef.hpp>
#include <Nebula/Util/shared.hpp>


namespace neb { namespace util {

	class terminal: virtual public neb::std::shared {
		public:
			terminal();
			void					operator<<(::std::string s);
			void					operator<<(char c);
			int					enter();


			/** @brief %command_set
			 *
			 * @note WEAK
			 */
			sp::shared_ptr<neb::util::command_set>		cs_;


			unsigned int					lines_max_;

			::std::deque< ::std::string >			lines_;
			::std::string					line_;


	};

}}

#endif
