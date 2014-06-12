#ifndef __NEBULA_UI_OBJECT_TERMINAL_H__
#define __NEBULA_UI_OBJECT_TERMINAL_H__

#include <deque>

#include <Nebula/Graphics/GUI/Object/Base.hh>

namespace neb {
	namespace gfx {
		namespace GUI {
			namespace Object {
				class terminal: public neb::gfx::GUI::Object::Base {
					public:
						enum
						{
							max_line_count = 10
						};

						//terminal();
						virtual void		draw(sp::shared_ptr<neb::glsl::program> p);
						//virtual void		connect();


						virtual int		key_fun(
								sp::shared_ptr<neb::gfx::Window::Base> const & window, int,int,int,int);


						virtual int		enter();
					public:
						::std::deque< ::std::string >		lines_;
						::std::string				line_;

				};
			}
		}
	}
}

#endif

