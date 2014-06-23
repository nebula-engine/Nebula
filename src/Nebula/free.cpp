#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <ft2build.h>
#include FT_FREETYPE_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
//#include <GL/gl.h>

#include <Galaxy-Log/log.hpp>

#include <Nebula/app/Base.hh>
#include <Nebula/gfx/window/Base.hh>
#include <Nebula/gfx/glsl/Uniform/scalar.hpp>
#include <Nebula/gfx/glsl/attrib.hh>

#include <Nebula/free.hh>

void		neb::init_log() {

	gal::log::min_severity["neb"]			= debug;
	gal::log::min_severity["neb app"]		= debug;
	gal::log::min_severity["neb timer"]		= debug;

	gal::log::min_severity["neb core scene"]	= debug;
	gal::log::min_severity["neb core actor"]	= debug;
	gal::log::min_severity["neb core shape"]	= debug;
	gal::log::min_severity["neb core light"]	= debug;

	gal::log::min_severity["neb gfx"]		= debug;
	gal::log::min_severity["neb gfx window"]	= debug;
	gal::log::min_severity["neb gfx context"]	= debug;

	gal::log::min_severity["neb gfx camera view"]	= debug;

	gal::log::min_severity["phx app"]		= debug;

	gal::log::min_severity["phx core scene"]	= debug;
	gal::log::min_severity["phx core actor"]	= debug;
	gal::log::min_severity["phx core shape"]	= debug;
	gal::log::min_severity["phx core light"]	= debug;

	gal::log::min_severity["phx game"]		= debug;
	gal::log::min_severity["phx game weapon"]	= debug;

	gal::log::init();

}
void		neb::init() {

	neb::init_log();
	
	neb::app::base::g_app_ = sp::make_shared<neb::app::base>();

	neb::app::base::g_app_->init();


}


