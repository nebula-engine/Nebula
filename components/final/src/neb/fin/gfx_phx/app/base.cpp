

#include <neb/gfx/gui/object/terminal.hh>

#include <fstream>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#include <map>

#include <ft2build.h>
#include FT_FREETYPE_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <gal/console/base.hpp>

#include <gal/log/log.hpp>

#include <neb/core/util/config.hpp>
#include <neb/core/util/log.hpp>
#include <neb/core/app/__base.hpp>
#include <neb/core/core/scene/base.hpp>


#include <neb/gfx/util/log.hpp>
#include <neb/gfx/Context/Base.hh>
#include <neb/gfx/window/Base.hh>

#include <neb/phx/util/log.hpp>


#include <neb/fin/gfx_phx/app/base.hpp>
#include <neb/fin/gfx_phx/core/scene/base.hpp>

#include <neb/py/config.hpp>
#include <neb/py/core/scene/base.hpp>

#define STRINGIZE2(x) #x
#define STRINGIZE(x) STRINGIZE2(x)

shared_ptr<neb::fin::gfx_phx::app::base>		neb::fin::gfx_phx::app::base::global() {
	auto app(dynamic_pointer_cast<neb::fin::gfx_phx::app::base>(g_app_));
	assert(app);
	return app;
}
shared_ptr<neb::fin::gfx_phx::app::base>		neb::fin::gfx_phx::app::base::init() {
	auto app(make_shared<neb::fin::gfx_phx::app::base>());

	app->neb::core::app::__base::__init();

	app->neb::gfx::app::__gfx::__init();
	app->neb::gfx::app::__gfx_glsl::__init();

	app->neb::phx::app::base::__init();

	app->neb::fin::gfx_phx::app::base::__init();

	g_app_ = app;
	return app;
}
neb::fin::gfx_phx::app::base::base() {
}
neb::fin::gfx_phx::app::base::~base() {
}
void				neb::fin::gfx_phx::app::base::__init() {

	try {
		console_->main_namespace_["neb"] = boost::python::import(STRINGIZE(PY_LIB_NAME));
	} catch(bp::error_already_set const &) {
		std::cout << "unhandled execption\n";
		// print all other errors to stderr
		PyErr_Print();
	}


	// log levels

	std::map<std::string, int> map_var({
			{"neb core",		0},
			{"neb core scene",	1},
			{"neb core actor",	2},
			{"neb core shape",	3},
			{"neb core light",	4},
			{"neb gfx",		5},
			{"neb gfx shape",	6},
			{"neb phx",		7},
			{"neb phx scene",	8},
			{"neb phx actor",	9},
			{"neb phx shape",	10}});
	std::map<std::string, int> map_val({
			{"debug",	debug},
			{"info",	info},
			{"warning",	warning},
			{"error",	error},
			{"critical",	critical}});


	std::ifstream ifs(share_dir_ + "config.txt");
	if(ifs.is_open()) {
		for(std::string line; std::getline(ifs, line);) {
			auto loc = line.find("=");
			if(loc != std::string::npos) {
				auto var = line.substr(0,loc);
				auto val = line.substr(loc+1);

				auto it_var = map_var.find(var);
				auto it_val = map_val.find(val);

				if(it_var == map_var.end()) {
					std::cout << "invalid variable" << std::endl;
					abort();
				}
				if(it_val == map_val.end()) {
					std::cout << "invalid value" << std::endl;
					abort();
				}
				
				switch(it_var->second) {
					case 0: neb::core::sl			= (severity_level)it_val->second; break;
					case 1: neb::core::core::scene::sl	= (severity_level)it_val->second; break;
					case 2: neb::core::core::actor::sl	= (severity_level)it_val->second; break;
					case 3: neb::core::core::shape::sl	= (severity_level)it_val->second; break;
					case 4: neb::core::core::light::sl	= (severity_level)it_val->second; break;
					case 5: neb::gfx::sl			= (severity_level)it_val->second; break;
					case 6: neb::gfx::core::shape::sl	= (severity_level)it_val->second; break;
					case 7: neb::phx::sl			= (severity_level)it_val->second; break;
					case 8: neb::phx::core::scene::sl	= (severity_level)it_val->second; break;
					case 9: neb::phx::core::actor::sl	= (severity_level)it_val->second; break;
					case 10: neb::phx::core::shape::sl	= (severity_level)it_val->second; break;
					default:
						std::cout << "default" << std::endl;
						abort();
				}
			}
		}
	}

}
void				neb::fin::gfx_phx::app::base::release() {
}
void				neb::fin::gfx_phx::app::base::loop() {

	auto self(std::dynamic_pointer_cast<neb::core::app::__base>(shared_from_this()));
	assert(self);
	
	//::std::thread t(::std::bind(&neb::app::base::loop2, self));
	
	
	while(!flag_.any(neb::core::app::util::flag::E::SHOULD_RELEASE)) {

		ts_.step(glfwGetTime());

		step(ts_);
		
		//::std::this_thread::yield();
	}
	
	//t.join();
	
//	if(server_) server_->close();
//	if(client_) client_->close();

}
void				neb::fin::gfx_phx::app::base::step(gal::etc::timestep const & ts) {

	neb::core::core::scene::util::parent::step(ts);

	neb::gfx::window::util::parent::step(ts);

	glfwPollEvents();
}
neb::core::pose						neb::fin::gfx_phx::app::base::getPose() {
	return neb::core::pose();
}
neb::core::pose						neb::fin::gfx_phx::app::base::getPoseGlobal() {
	return neb::core::pose();
}
void							neb::fin::gfx_phx::app::base::loadXml(::std::string filename, neb::stl::wrapper& w) {
}
void							neb::fin::gfx_phx::app::base::set_should_release() {
}
weak_ptr<neb::fin::gfx_phx::core::scene::base>		neb::fin::gfx_phx::app::base::createScene() {
	auto self(dynamic_pointer_cast<neb::fin::gfx_phx::app::base>(shared_from_this()));

	auto scene(make_shared<neb::fin::gfx_phx::core::scene::base>(self));

	neb::core::core::scene::util::parent::insert(scene);

	scene->init();

	// python object
	if(console_) {
		neb::py::core::scene::base py_scene;
		py_scene.scene_ = scene;
	
		try {
			console_->main_namespace_["scene"] = py_scene;
		} catch(bp::error_already_set const &) {
			cout << "unhandled execption\n";
			PyErr_Print();
		}
	}

	return scene;
}




