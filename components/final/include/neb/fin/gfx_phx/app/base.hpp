#ifndef __NEBULA_APP_H__
#define __NEBULA_APP_H__

#include <fstream>

#include <boost/archive/polymorphic_xml_iarchive.hpp>

#include <ft2build.h>
#include FT_FREETYPE_H

#include <gal/itf/shared.hpp>

#include <neb/core/app/__core.hpp>
#include <neb/core/core/scene/util/parent.hpp>
#include <neb/core/core/shape/util/decl.hpp>
#include <neb/core/util/wrapper.hpp>
#include <neb/core/util/decl.hpp>

#include <neb/gfx/app/__gfx.hpp>
#include <neb/gfx/app/__gfx_glsl.hpp>
#include <neb/gfx/app/glfw.hpp>
#include <neb/gfx/util/decl.hpp>
#include <neb/gfx/window/Base.hh>
#include <neb/gfx/window/util/Parent.hh>
#include <neb/gfx/gui/layout/util/parent.hpp>

#include <neb/phx/app/base.hpp>

#include <neb/fin/gfx_phx/core/scene/util/decl.hpp>

namespace neb {
	namespace fin {
		namespace gfx_phx {
			namespace app {
				/** @brief Base
				 *
				 * final implementation
				 */
				class base:
					virtual public neb::app::__core,
					virtual public neb::gfx::app::__gfx,
					virtual public neb::gfx::app::__gfx_glsl,
					virtual public neb::gfx::app::glfw,
					virtual public neb::phx::app::base,
					virtual public neb::gfx::gui::layout::util::parent
				{
					public:
						typedef std::weak_ptr<neb::fin::gfx_phx::core::scene::base>	scene_w;
					public:
						static std::shared_ptr<neb::fin::gfx_phx::app::base>		global();
						static std::shared_ptr<neb::fin::gfx_phx::app::base>		s_init();
					public:
						base();
						virtual ~base();
					protected:
						virtual void						init();
					public:
						neb::core::pose						getPose();
						neb::core::pose						getPoseGlobal();
						void							loadXml(::std::string filename, neb::stl::wrapper& w);
					public:
						void							release();
						virtual void						step(gal::etc::timestep const & ts);
						void							loop();
						void							set_should_release();
						scene_w				createScene();
						scene_w				createSceneDll(std::string);

				};
			}
		}
	}
}

#endif

