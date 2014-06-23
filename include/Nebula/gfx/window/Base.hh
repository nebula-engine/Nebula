#ifndef __GRU_WINDOW_H__
#define __GRU_WINDOW_H__

#include <functional>
#include <vector>
#include <map>

//#include <Nebula/config.hh>
#include <Nebula/util/decl.hpp>
#include <gal/std/timestep.hpp>
#include <Nebula/core/scene/Util/Types.hh>

#include <Nebula/gfx/Context/Base.hh>
#include <Nebula/gfx/Context/Util/Parent.hh>
#include <Nebula/gfx/util/decl.hpp>
#include <Nebula/gfx/texture.hh>
//#include <Nebula/core/light/Base.hh>
#include <Nebula/gfx/glsl/program.hh>
#include <Nebula/gfx/glsl/shader.hh>
#include <Nebula/gfx/GUI/Layout/Base.hh>
#include <Nebula/gfx/window/__base.hpp>
#include <Nebula/gfx/window/util/Flag.hh>
#include <Nebula/gfx/window/util/Cast.hh>

#include <Nebula/gfx/window/util/signals.hpp>



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
						neb::Signals::KeyFun		key_fun_;
						neb::Signals::MouseButtonFun	mouse_button_fun_;
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








