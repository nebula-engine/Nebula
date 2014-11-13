#ifndef __GRU_WINDOW_H__
#define __GRU_WINDOW_H__

#include <functional>
#include <vector>
#include <map>

#include <gal/etc/timestep.hpp>

#include <neb/core/util/decl.hpp>
#include <neb/core/core/scene/util/decl.hpp>
#include <neb/core/input/source.hpp>
#include <neb/core/input/callback.hpp>

#include <neb/gfx/Context/Base.hh>
#include <neb/gfx/Context/Util/Parent.hh>
#include <neb/gfx/util/decl.hpp>
#include <neb/gfx/util/decl.hpp>
#include <neb/gfx/texture.hpp>
#include <neb/gfx/glsl/program/base.hpp>
#include <neb/gfx/glsl/shader.hh>
#include <neb/gfx/gui/layout/base.hpp>
#include <neb/gfx/window/__base.hpp>
#include <neb/gfx/window/util/Flag.hh>
#include <neb/gfx/window/util/Cast.hh>

namespace neb { namespace gfx { namespace window {
	class base:
		virtual public neb::gfx::window::__base,
		virtual public neb::gfx::context::util::parent,
		virtual public neb::gfx::window::util::cast,
		virtual public neb::core::input::source,
		virtual public neb::core::input::callback
	{
		public:
			typedef neb::gfx::window::util::parent parent_t;
			typedef neb::util::parent<neb::gfx::context::base, neb::gfx::context::util::parent> contexts;

			base();
			virtual ~base();
			virtual void				init(parent_t * const & p);
			virtual void				release();
			
			virtual glm::vec2			getCursorPosNDC();

			/** @name Main Loop @{ */
			virtual void				render();
			virtual void				step(gal::etc::timestep const & ts);
			/** @} */
			void					resize();

			void					callback_window_pos_fun(GLFWwindow*,int,int);
			void					callback_window_size_fun(GLFWwindow*,int,int);
			void					callback_window_close_fun(GLFWwindow*);
			void					callback_window_refresh_fun(GLFWwindow*);
			void					callback_mouse_button_fun(GLFWwindow*,int,int,int);
			void					callback_key_fun(GLFWwindow*,int,int,int,int);
			void					callbackCharFun(GLFWwindow*,unsigned int);

			std::weak_ptr<neb::gfx::context::window>	createContextTwo();
			std::weak_ptr<neb::gfx::context::window>	createContextThree();
			std::weak_ptr<neb::gfx::context::window>	createContextNormalMap();

			void						makeCurrent();

			void						printScreen();
		public:


			static GLFWwindow*				first_window_;


			neb::gfx::window::util::Flag	flag_;
			int					x_;
			int					y_;
			int					w_;
			int					h_;
			::std::string				title_;


			GLFWwindow*		window_;

			//int			windowID;

			// persistent buffer for screen print
			std::vector<unsigned char>		screenBuffer_;

		public:

	};
}
}
}


#endif








