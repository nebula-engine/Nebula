#ifndef __NEBULA_APP_GFX_WINDOW_H__
#define __NEBULA_APP_GFX_WINDOW_H__

#include <fstream>
#include <exception>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <boost/asio/io_service.hpp>
#include <boost/archive/polymorphic_xml_iarchive.hpp>

#include <gal/itf/shared.hpp>

#include <neb/core/util/decl.hpp>
#include <neb/core/app/__base.hpp>

#include <neb/gfx/util/decl.hpp>
#include <neb/gfx/gui/layout/util/parent.hpp>
#include <neb/gfx/window/util/Parent.hh>
#include <neb/gfx/Context/Util/Parent.hh>

namespace neb { namespace gfx {
	
	namespace app {
		/** @brief gfx
		 * 
		 * graphics and window handling
		 */
		class glfw:
			virtual public neb::core::app::__base,
			virtual public neb::gfx::window::util::parent
		{
			public:
				typedef std::map< GLFWwindow*, std::shared_ptr<neb::gfx::window::base> >			glfwwindow_map_type;
			
				static neb::gfx::app::glfw * const		global();

				static void					static_error_fun(int,char const *);
				static void					static_window_pos_fun(GLFWwindow*,int,int);
				static void					static_window_size_fun(GLFWwindow*,int,int);
				static void					static_window_close_fun(GLFWwindow*);
				static void					static_window_refresh_fun(GLFWwindow*);
				//static void					static_window_focus_fun(GLFWwindow*,int);
				//static void					static_window_iconify_fun(GLFWwindow*,int);
				//static void					static_window_buffer_size_fun(GLFWwindow*,int,int);
				static void					static_mouse_button_fun(GLFWwindow*,int,int,int);
				static void					static_key_fun(GLFWwindow*,int,int,int,int);
				static void					staticCharFun(GLFWwindow*,unsigned int);


				void						init();
				void						init_glew();
				void						release();
				void						step(gal::etc::timestep const & ts);
				void						render();
				


				std::weak_ptr<neb::gfx::window::base>		get_window(GLFWwindow*);

			public:

				//GLFWwindow*					currentIdleWindow_;
				glfwwindow_map_type				windows_glfw_;

		};
}}}

#endif




