#ifndef __NEBULA_UI_OBJECT_TERMINAL_H__
#define __NEBULA_UI_OBJECT_TERMINAL_H__

#include <deque>

#include <Nebula/Graphics/GUI/Object/Base.hh>

namespace Neb {
	namespace Graphics {
		namespace GUI {
			namespace Object {
				class terminal: public Neb::Graphics::GUI::Object::Base {
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
}

#endif

