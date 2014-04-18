#ifndef __NEBULA_UI_OBJECT_TERMINAL_H__
#define __NEBULA_UI_OBJECT_TERMINAL_H__

#include <glutpp/gui/object/textview.h>

namespace glutpp { namespace gui { namespace object {

	class terminal:
		public glutpp::gui::object::object
	{
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

