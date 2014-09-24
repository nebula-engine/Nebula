#ifndef NEBULA_UTIL_TERMINAL_BASE_HPP
#define NEBULA_UTIL_TERMINAL_BASE_HPP

#include <string>
#include <deque>
#include <sstream>

#include <gal/console/__base.hpp>
#include <gal/console/sstream.hpp>


namespace gal { namespace console {
	class base: virtual public gal::console::__base {
		public:
			base();
			virtual ~base() {}
	
			/** @brief push formatted text into terminal history */
			template<typename T> gal::console::stringstream		operator<<(T const & t) {
				gal::console::stringstream ss(std::dynamic_pointer_cast<gal::console::base>(shared_from_this()));
				return ::std::move(ss << t);
			}

			/** @brief push character onto current line */
			void							push(char c);
			
			virtual void						enter() = 0;





			/** @brief evaluate
			 * @note backend
			 */
			virtual void						eval(::std::string const & s) = 0;


		protected:


	};
}}

#endif



