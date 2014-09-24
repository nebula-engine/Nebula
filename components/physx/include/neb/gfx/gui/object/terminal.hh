#ifndef __NEBULA_UI_OBJECT_TERMINAL_H__
#define __NEBULA_UI_OBJECT_TERMINAL_H__

#include <deque>

#include <neb/core/app/__base.hpp>

#include <neb/gfx/gui/object/Base.hh>



namespace neb { namespace gfx { namespace gui { namespace object {
	class terminal:
		virtual public neb::gfx::gui::object::base
	{
		public:
			typedef typename neb::gfx::gui::object::base::parent_t parent_t;

			terminal();
			virtual void			init(parent_t * const & p);
			virtual void			step(gal::etc::timestep const &) {}
			virtual void			draw(RenderDesc const &);

			virtual int			keyFun(
					std::shared_ptr<neb::core::input::source> const &, int,int,int,int);
			virtual int			charFun(
					std::shared_ptr<neb::core::input::source> const &,
					unsigned int codepoint);



			std::weak_ptr<neb::core::app::__base::console_type>		console_;

			// display
			std::vector<std::string>		history_;
			unsigned int				history_current_;
			unsigned int				page_offset_;
			unsigned int				max_line_count_;
	};
}}}}

#endif

