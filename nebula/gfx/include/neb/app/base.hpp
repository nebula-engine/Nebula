#ifndef __NEBULA_APP_H__
#define __NEBULA_APP_H__

#include <fstream>

#include <boost/archive/polymorphic_xml_iarchive.hpp>

#include <ft2build.h>
#include FT_FREETYPE_H

#include <Galaxy-Standard/shared.hpp>
//#include <Galaxy-Standard/terminal/command_set.hpp>

#include <Galaxy-Network/decl.hpp>

#include <neb/core/free.hpp>
#include <neb/util/decl.hpp>
#include <neb/app/__core.hpp>
#include <neb/app/__gfx.hpp>
#include <neb/app/__gfx_glsl.hpp>
//#include <neb/app/__net.hpp>

#include <neb/core/scene/util/Parent.hh>

#include <neb/gfx/util/decl.hpp>
#include <neb/gfx/window/Base.hh>
#include <neb/gfx/window/util/Parent.hh>
#include <neb/gfx/GUI/Layout/util/Parent.hh>
#include <neb/core/shape/util/Types.hh>
#include <neb/util/wrapper.hpp>
#include <neb/game/game/util/parent.hpp>

namespace gal { namespace std {
	class command_set;
}}

namespace neb { namespace app {


		/** @brief Base
		 *
		 * final implementation
		 */
		class base:
			virtual public neb::app::__gfx,
			virtual public neb::app::__gfx_glsl,
			virtual public neb::app::__core,
			/*virtual public neb::app::__net,*/
			virtual public neb::game::game::util::parent
		{
			public:
				friend void neb::init();
			public:
				base();
				virtual ~base();
			public:
				//void						command(sp::shared_ptr<neb::gfx::gui::object::terminal> term, ::std::string);
			public:
				neb::core::pose						getPose();
				neb::core::pose						getPoseGlobal();

				static sp::shared_ptr<neb::app::base>		global();

				void						loadXml(::std::string filename, neb::std::wrapper& w);

				sp::shared_ptr<neb::gfx::window::base>						get_window(GLFWwindow*);

			private:
			public:
				void					init();
				void					release() {}

				void					init_glew();

				virtual void				step1(gal::std::timestep const & ts);
				virtual void				step2(gal::std::timestep const & ts);
	
				void					loop1();
				void					loop2();

				void					set_should_release();



			public:
			

				sp::shared_ptr<gal::std::command_set>				command_set_;
		};



}}

#endif





