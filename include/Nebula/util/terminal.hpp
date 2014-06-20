#ifndef NEBULA_UTIL_TERMINAL_HPP
#define NEBULA_UTIL_TERMINAL_HPP

#include <string>
#include <deque>
#include <sstream>

#include <Nebula/util/decl.hpp>
#include <Nebula/util/typedef.hpp>
#include <Nebula/util/shared.hpp>


namespace neb { namespace util {

	class __terminal_data: virtual public neb::std::shared {
		public:
			::std::deque< ::std::string >			lines_;
			::std::stringstream				ss_;
	};

	/** @brief temporary stringstream */
	struct stringstream {
		stringstream(sp::shared_ptr<neb::util::__terminal_data> t);
		stringstream(stringstream&& ss);
		~stringstream();
		template<typename T> stringstream		operator<<(T const & t) {
			assert(t_);
			t_->ss_ << t;
			return ::std::move(*this);
		}
		sp::shared_ptr<neb::util::__terminal_data>		t_;
	};

	/** @brief terminal */
	class terminal: virtual public neb::util::__terminal_data {
		public:
			terminal();
			
			/** @brief push formatted text into terminal history */
			template<typename T> neb::util::stringstream		operator<<(T const & t) {
				neb::util::stringstream ss(sp::dynamic_pointer_cast<neb::util::terminal>(shared_from_this()));
				return ::std::move(ss << t);
			}
			/** @brief push character onto current line */
			void							push(char c);
			int							enter();


			/** @brief %command_set
			 *
			 * @note WEAK
			 */
			sp::shared_ptr<neb::util::command_set>		cs_;


			unsigned int					lines_max_;

			::std::string					line_;

			

	};

}}

#endif
