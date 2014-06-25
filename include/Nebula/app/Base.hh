#ifndef __NEBULA_APP_H__
#define __NEBULA_APP_H__

#include <fstream>

#include <boost/archive/polymorphic_xml_iarchive.hpp>

#include <ft2build.h>
#include FT_FREETYPE_H

#include <Galaxy-Standard/shared.hpp>
#include <Galaxy-Standard/terminal/command_set.hpp>

#include <Galaxy-Network/decl.hpp>

#include <Nebula/free.hh>
#include <Nebula/util/decl.hpp>
#include <Nebula/app/__core.hpp>
#include <Nebula/app/__gfx.hpp>
#include <Nebula/app/__gfx_glsl.hpp>
#include <Nebula/app/__net.hpp>

#include <Nebula/net/server.hh>
#include <Nebula/net/client.hh>
#include <Nebula/message/Types.hh>
#include <Nebula/core/scene/Util/Parent.hh>

#include <Nebula/gfx/util/decl.hpp>
#include <Nebula/gfx/window/Base.hh>
#include <Nebula/gfx/window/util/Parent.hh>
#include <Nebula/gfx/GUI/Layout/Util/Parent.hh>
#include <Nebula/core/shape/Util/Types.hh>
#include <Nebula/util/wrapper.hpp>
#include <Nebula/game/game/util/parent.hpp>

namespace neb { namespace app {


		/** @brief Base
		 *
		 * final implementation
		 */
		class base:
			virtual public neb::app::__gfx,
			virtual public neb::app::__gfx_glsl,
			virtual public neb::app::__core,
			virtual public neb::app::__net,
			virtual public neb::game::game::util::parent
		{
			public:
				friend void neb::init();
			public:
				base();
				virtual ~base();
			public:
				void						command(sp::shared_ptr<neb::gfx::gui::object::terminal> term, ::std::string);
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
				virtual void				step(gal::std::timestep const & ts);
				int					loop();

				void					set_should_release();


				/** @name %Network @{ */

				void					transmit_scenes(sp::shared_ptr<neb::Network::Communicating>);
				/** @} */

			public:
				static sp::shared_ptr<neb::app::base>				g_app_;

				gal::std::timestep						ts_;
			

				sp::shared_ptr<gal::std::command_set>				command_set_;
		};



}}

#endif





