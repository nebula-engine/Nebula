

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
#include <gal/etc/stopwatch.hpp>
#include <gal/dll/helper.hpp>

#include <gal/log/log.hpp>

#include <neb/core/util/config.hpp>
#include <neb/core/util/log.hpp>
#include <neb/core/app/__base.hpp>
#include <neb/core/core/scene/base.hpp>

#include <gal/stl/deleter.hpp>

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
shared_ptr<neb::fin::gfx_phx::app::base>		neb::fin::gfx_phx::app::base::s_init() {

	typedef neb::fin::gfx_phx::app::base T;
	
	std::shared_ptr<T> app(new T(), gal::stl::deleter<T>());
	
	app->neb::core::app::__base::init();

	app->neb::gfx::app::__gfx::init();
	app->neb::gfx::app::__gfx_glsl::__init();
	app->neb::gfx::app::glfw::init();

	app->neb::phx::app::base::__init();

	app->neb::fin::gfx_phx::app::base::init();

	g_app_ = app;
	return app;
}
neb::fin::gfx_phx::app::base::base() {
}
neb::fin::gfx_phx::app::base::~base() {
	std::cout << __PRETTY_FUNCTION__ << std::endl;
}
void				neb::fin::gfx_phx::app::base::init() {

	try {
		console_->main_namespace_["neb"] = boost::python::import(STRINGIZE(PY_LIB_NAME));
	} catch(bp::error_already_set const &) {
		std::cout << "unhandled execption\n";
		// print all other errors to stderr
		PyErr_Print();
	}


	// log levels

	struct Pair {
		char const *		c;
		severity_level * const	sl;
	};

	static const Pair pairs[13] = {
		{"neb core",		&neb::core::sl},
		{"neb core scene",	&neb::core::core::scene::sl},
		{"neb core actor",	&neb::core::core::actor::sl},
		{"neb core shape",	&neb::core::core::shape::sl},
		{"neb core light",	&neb::core::core::light::sl},
		{"neb gfx",		&neb::gfx::sl},
		{"neb gfx actor",	&neb::gfx::core::actor::sl},
		{"neb gfx shape",	&neb::gfx::core::shape::sl},
		{"neb gfx light",	&neb::gfx::core::light::sl},
		{"neb phx",		&neb::phx::sl},
		{"neb phx scene",	&neb::phx::core::scene::sl},
		{"neb phx actor",	&neb::phx::core::actor::sl},
		{"neb phx shape",	&neb::phx::core::shape::sl}
	};


/*	std::map<std::string, int> map_var({
			{"neb core",		0},
			{"neb core scene",	1},
			{"neb core actor",	2},
			{"neb core shape",	3},
			{"neb core light",	4},
			{"neb gfx",		5},
			{"neb gfx actor",	6},
			{"neb gfx shape",	7},
			{"neb gfx light",	8},
			{"neb phx",		9},
			{"neb phx scene",	10},
			{"neb phx actor",	11},
			{"neb phx shape",	12}});
			*/
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
	
				auto it_val = map_val.find(val);
				if(it_val == map_val.end()) {
					std::cout << "invalid value" << std::endl;
					abort();
				}
				
				unsigned int i = 0;
				for(i = 0; i < (sizeof(pairs) / sizeof(Pair)); i++)
				{
					if(strcmp(var.c_str(), pairs[i].c) == 0)
					{
						*pairs[i].sl = (severity_level)it_val->second;
						break;
					}
				}
				if(i == (sizeof(pairs) / sizeof(Pair)))
				{
					 std::cout << "log group not found: '" << var << "'" << std::endl;
					 abort();
				}

				/*
				auto it_var = map_var.find(var);

				if(it_var == map_var.end()) {
					std::cout << "invalid variable" << std::endl;
					abort();
				}

				switch(it_var->second) {
					case 0: neb::core::sl			= (severity_level)it_val->second; break;
					case 1: neb::core::core::scene::sl	= (severity_level)it_val->second; break;
					case 2: neb::core::core::actor::sl	= (severity_level)it_val->second; break;
					case 3: neb::core::core::shape::sl	= (severity_level)it_val->second; break;
					case 4: neb::core::core::light::sl	= (severity_level)it_val->second; break;
					case 5: neb::gfx::sl			= (severity_level)it_val->second; break;
					case 6: neb::gfx::core::actor::sl	= (severity_level)it_val->second; break;
					case 7: neb::gfx::core::shape::sl	= (severity_level)it_val->second; break;
					case 8: neb::gfx::core::light::sl	= (severity_level)it_val->second; break;
					case 9: neb::phx::sl			= (severity_level)it_val->second; break;
					case 10: neb::phx::core::scene::sl	= (severity_level)it_val->second; break;
					case 11: neb::phx::core::actor::sl	= (severity_level)it_val->second; break;
					case 12: neb::phx::core::shape::sl	= (severity_level)it_val->second; break;
					default:
						 std::cout << "default" << std::endl;
						 abort();
				}
				*/
			}
		}
	}

}
void				neb::fin::gfx_phx::app::base::release()
{
	//neb::core::app::__base::__release();
	neb::app::__core::__release();

	neb::gfx::app::__gfx::release();
	//neb::gfx::app::__gfx_glsl::__release();

	neb::phx::app::base::__release();

}
void				neb::fin::gfx_phx::app::base::loop() {

	auto self(std::dynamic_pointer_cast<neb::core::app::__base>(shared_from_this()));
	assert(self);

	//::std::thread t(::std::bind(&neb::app::base::loop2, self));

	static gal::etc::stopwatch sw_step;
	static gal::etc::stopwatch sw_render;

	double t;

	while(!flag_.any(neb::core::app::util::flag::E::SHOULD_RELEASE)) {

		if(!neb::gfx::window::util::parent::map_.front()) break;

		t = glfwGetTime();
		sw_step.start(t);
		{
			ts_.step(t);
			step(ts_);
		}
		t = glfwGetTime();
		sw_step.stop(t);


		t = glfwGetTime();
		sw_render.start(t);
		{
			neb::gfx::app::glfw::render();

			//::std::this_thread::yield();
		}
		t = glfwGetTime();
		sw_render.stop(t);

		if((ts_.frame % 100) == 0)
		{
			std::cout
				<< std::setw(16) << "step"
				<< std::setw(16) << sw_step.getAvg()
				<< std::setw(16) << "render"
				<< std::setw(16) << sw_render.getAvg()
				<< std::endl;
		}
		//t.join();

		//	if(server_) server_->close();
		//	if(client_) client_->close();

	}
}
void				neb::fin::gfx_phx::app::base::step(gal::etc::timestep const & ts) {

	neb::core::core::scene::util::parent::step(ts);

	neb::gfx::gui::layout::util::parent::step(ts);

	neb::game::game::util::parent::step(ts);

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
std::weak_ptr<neb::fin::gfx_phx::core::scene::base>		neb::fin::gfx_phx::app::base::createScene()
{
	auto self(dynamic_pointer_cast<neb::fin::gfx_phx::app::base>(shared_from_this()));

	typedef neb::fin::gfx_phx::core::scene::base T;

	std::shared_ptr<T> scene (new T, gal::stl::deleter<T>());

	neb::core::core::scene::util::parent::insert(scene);

	scene->init(this);

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

		//try {
			console_->eval(
					"def on_exit(sig, func=None):\n"
					"    print \"exit handler\"\n"
					"    import time\n"
					"    time.sleep(10)"
					);
			console_->eval(
					"set_exit_handler(on_exit)"
					);
			console_->eval(
					"print on_exit"
					);
		//} catch(bp::error_already_set const &) {
		//	cout << "unhandled execption\n";
		//	PyErr_Print();
		//}

	}

	return scene;
}
std::weak_ptr<neb::fin::gfx_phx::core::scene::base>		neb::fin::gfx_phx::app::base::createSceneDll(std::string dll_name)
{
	auto self(dynamic_pointer_cast<neb::fin::gfx_phx::app::base>(shared_from_this()));

	typedef neb::fin::gfx_phx::core::scene::base		T;
	typedef gal::dll::helper<T>				H;

	std::shared_ptr<H> h(new H(dll_name, "scene"));
	h->open();
	
	std::shared_ptr<T> scene = h->make_shared();

	neb::core::core::scene::util::parent::insert(scene);

	scene->init(this);

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

		console_->eval(
				"import os, sys\n"
				"def set_exit_handler(func):\n"
				"    if os.name == \"nt\":\n"
				"        try:\n"
				"            import win32api\n"
				"            win32api.SetConsoleCtrlHandler(func, True)\n"
				"        except ImportError:\n"
				"            version = \".\".join(map(str, sys.version_info[:2]))\n"
				"            raise Exception(\"pywin32 not installed for Python \" + version)\n"
				"    else:\n"
				"        import signal\n"
				"        signal.signal(signal.SIGTERM, func)"
			      );

		console_->eval(
				"def on_exit(sig, func=None):\n"
				"    print \"exit handler\"\n"
				"    import time\n"
				"    time.sleep(10)"
			      );
		console_->eval(
				"set_exit_handler(on_exit)"
			      );
		console_->eval(
				"print on_exit"
			      );




	}

	return scene;
}




