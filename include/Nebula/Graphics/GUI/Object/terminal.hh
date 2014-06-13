#ifndef __NEBULA_UI_OBJECT_TERMINAL_H__
#define __NEBULA_UI_OBJECT_TERMINAL_H__

#include <deque>

#include <Nebula/Util/terminal.hpp>
#include <Nebula/Graphics/GUI/Object/Base.hh>

namespace neb {	namespace gfx {	namespace gui {	namespace object {


	class terminal:
		virtual public neb::gfx::gui::object::Base,
		virtual public neb::util::terminal
	{
		public:
			enum
			{
				max_line_count = 10
			};

			//terminal();

			virtual void		init();

			virtual void		draw(sp::shared_ptr<neb::glsl::program> p);
			//virtual void		connect();


			virtual int		key_fun(
					sp::shared_ptr<neb::gfx::Window::Base> const & window, int,int,int,int);

	};



}}}}

#endif

