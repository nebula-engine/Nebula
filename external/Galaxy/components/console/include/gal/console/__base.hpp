#ifndef GALAXY_CONSOLE___BASE_HPP
#define GALAXY_CONSOLE___BASE_HPP

#include <string>
#include <deque>
#include <sstream>

#include <gal/itf/shared.hpp>

template<typename T> struct scroller {
	scroller(): pos(0) {}

	T&		operator=(T const & t) {
		container = t;
		return container;
	}

	template<typename U> void	insert(U const & u) {
		container.insert(pos, u);
		pos++;
	}
	void				backspace() {
		if(!container.empty() && pos > 0) {
			pos--;
			container.erase(pos, 1);
		}
	}
	void				del() {
		if(!container.empty() && pos < container.size()) {
			container.erase(pos, 1);
		}
	}
	void				clear() {
		container.clear();
		pos = 0;
	}
	void		up() {
		if(pos < container.size()) pos++;
	}
	void		down() {
		if(pos > 0) pos--;
	}
	
	
	typename T::size_type	pos;
	
	T		container;
};

namespace gal { namespace console {
	
	class __base: virtual public gal::itf::shared {
		public:
			/** @brief write line
			 * @note frontend
			 *
			 * add line to terminal history
			 */
			virtual void						write_line(::std::string const & s) = 0;

<<<<<<< HEAD

=======
			virtual void						release();
>>>>>>> d0f62233eb8fed722542d3bfcc237575d904a507

			std::stringstream					ss_;

			scroller<std::string>					line_;
			std::string						prompt_end_;

	};
	
}}

#endif
