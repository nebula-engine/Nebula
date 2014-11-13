#ifndef __NEBULA_APP_GFX_H__
#define __NEBULA_APP_GFX_H__

#include <fstream>
#include <exception>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <boost/asio/io_service.hpp>
#include <boost/archive/polymorphic_xml_iarchive.hpp>

#include <ft2build.h>
#include FT_FREETYPE_H

#include <neb/core/util/decl.hpp>
#include <neb/core/app/__base.hpp>
#include <neb/gfx/util/decl.hpp>

namespace neb { namespace gfx {
	
	struct exception: std::exception
	{
		virtual const char *		what()
		{
			return "graphics exception";
		}
	};
	
	namespace app {
		/** @brief gfx
		 * 
		 * graphics and window handling
		 */
		class __gfx:
			virtual public neb::core::app::__base
		{
			public:
			
				void						init();
				void						release();
				void						step(gal::etc::timestep const & ts);
				void						render();


				static std::weak_ptr<neb::gfx::app::__gfx>		global();


		// replaced with gal::parent::create()
		//		std::weak_ptr<neb::gfx::gui::layout::base>	createLayout();
		//		std::weak_ptr<neb::gfx::window::base>		createWindow();
			public:

				//GLFWwindow*								currentIdleWindow_;

				FT_Library								ft_;
				FT_Face									face_;
		};
}}}

#endif





