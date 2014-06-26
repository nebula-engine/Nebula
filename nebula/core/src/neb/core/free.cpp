#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fstream>

#include <ft2build.h>
#include FT_FREETYPE_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
//#include <GL/gl.h>

#include <boost/archive/xml_iarchive.hpp>

#include <Galaxy-Log/log.hpp>

#include <neb/util/debug.hpp>
#include <neb/app/Base.hh>
#include <neb/gfx/window/Base.hh>
#include <neb/gfx/glsl/Uniform/scalar.hpp>
#include <neb/gfx/glsl/attrib.hh>

#include <neb/free.hh>

void		neb::init_log() {
	
	neb::util::debug_options o;
	
	::std::ifstream f;
	f.open("debug_options.xml", ::std::ifstream::in);
	if(f.is_open()) {
		boost::archive::xml_iarchive ar(f);
		o.serialize(ar,0);
	}
	
	for(auto p : o.map_) {
		gal::log::min_severity[p.first] = (severity_level)p.second;
	}

/*	gal::log::min_severity["neb"]			= debug;
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
	gal::log::min_severity["phx game weapon"]	= debug;*/

	gal::log::init();

}
void		neb::init() {

	neb::init_log();
	
	neb::app::base::g_app_ = sp::make_shared<neb::app::base>();

	neb::app::base::g_app_->init();


}


