#ifndef __GRU_WINDOW_H__
#define __GRU_WINDOW_H__

#include <functional>
#include <vector>
#include <map>

//#include <neb/config.hh>
#include <neb/util/decl.hpp>
#include <gal/std/timestep.hpp>
#include <neb/core/scene/Util/Types.hh>

#include <neb/gfx/Context/Base.hh>
#include <neb/gfx/Context/Util/Parent.hh>
#include <neb/gfx/util/decl.hpp>
#include <neb/gfx/texture.hh>
//#include <neb/core/light/base.hpp>
#include <neb/gfx/glsl/program.hh>
#include <neb/gfx/glsl/shader.hh>
#include <neb/gfx/GUI/Layout/Base.hh>
#include <neb/gfx/window/__base.hpp>
#include <neb/gfx/window/util/Flag.hh>
#include <neb/gfx/window/util/Cast.hh>

#include <neb/gfx/window/util/signals.hpp>



namespace neb { namespace gfx { namespace window {


			class base:
				virtual public neb::gfx::window::__base,
				virtual public neb::gfx::context::util::parent,
				virtual public neb::gfx::window::util::cast
			{
				public:
					base();
					base(sp::shared_ptr<neb::gfx::window::util::parent> parent);
					virtual ~base();
				
				public:
					virtual void				init();
					virtual void				release();
	
					/** @name Main Loop @{ */
					void					render();
					void					step(gal::std::timestep const & ts);
					/** @} */
					void					resize();
	
					void					callback_window_pos_fun(GLFWwindow*,int,int);
					void					callback_window_size_fun(GLFWwindow*,int,int);
					void					callback_window_close_fun(GLFWwindow*);
					void					callback_window_refresh_fun(GLFWwindow*);
					void					callback_mouse_button_fun(GLFWwindow*,int,int,int);
					void					callback_key_fun(GLFWwindow*,int,int,int,int);
				public:
					sp::shared_ptr<neb::gfx::window::util::parent>			parent_;
					/** @brief self
					 *
					 * avoid casting shared_from_this
					 */
					sp::shared_ptr<neb::gfx::window::base>		self_;

					// input signals
					struct
					{
						neb::gfx::window::signals::KeyFun		key_fun_;
						neb::gfx::window::signals::MouseButtonFun	mouse_button_fun_;
					} sig_;


					
					
	
					neb::gfx::window::util::Flag	flag_;
					int					x_;
					int					y_;
					int					w_;
					int					h_;
					::std::string				title_;
					
					
					GLFWwindow*		window_;
					
					//int			windowID;
	
				public:

			};
		}
	}
}


#endif








