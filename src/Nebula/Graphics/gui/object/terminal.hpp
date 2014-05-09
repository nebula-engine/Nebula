#ifndef __NEBULA_UI_OBJECT_TERMINAL_H__
#define __NEBULA_UI_OBJECT_TERMINAL_H__

#include <deque>

#include <Nebula/Graphics/gui/object/textview.hpp>

namespace Neb {
	namespace gui {
		namespace object {
			class terminal: public Neb::gui::object::object {
				public:
					enum
					{
						max_line_count = 10
					};

					//terminal();
					virtual void		draw();
					//virtual void		connect();


					virtual int		key_fun(int,int,int,int);


					virtual int		enter();
				public:
					std::deque<std::string>		lines_;
					std::string			line_;

			};
		}
	}
}

#endif

