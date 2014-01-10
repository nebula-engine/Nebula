#include <algorithm>

#include <glutpp/renderable.h>
#include <glutpp/window/desc.h>
#include <glutpp/window/window.h>
#include <glutpp/scene/desc.h>

#include <glutpp/network/message.h>

#include <neb/config.h>
#include <neb/app.h>
#include <neb/physics.h>
#include <neb/packet/packet.h>

neb::app::app() {
	NEBULA_DEBUG_0_FUNCTION;
}
void	neb::app::init() {
	NEBULA_DEBUG_0_FUNCTION;
}
glutpp::window::window_shared neb::app::create_window(int w, int h, int x, int y, char const * title) {
	NEBULA_DEBUG_0_FUNCTION;

	glutpp::window::desc_shared wd(new glutpp::window::desc(w,h,x,y,title));
	
	auto window = glutpp::__master.create_window<glutpp::window::window>(wd);
	
	window->resize();
	
	windows_.push_back(window);
	
	return window;
}
void neb::app::load_scene_local(glutpp::scene::desc_shared sd) {
	NEBULA_DEBUG_0_FUNCTION;

	neb::scene::scene_shared scene(new neb::scene::scene(shared_from_this()));
	
	scene->init(sd);
	scene->user_type_ = neb::scene::scene::LOCAL;
	
	scenes_.push_back(scene);
}
void neb::app::load_scene_remote(glutpp::scene::desc_shared sd) {
	NEBULA_DEBUG_0_FUNCTION;

	neb::scene::scene_shared scene(new neb::scene::scene(shared_from_this()));
	
	scene->init(sd);
	scene->user_type_ = neb::scene::scene::REMOTE;
	
	int i = scene->i();//desc_->raw_.i_;

	assert(i != -1);
	
	scenes_[i] = scene;
}
void neb::app::load_layout(int name, char const * filename) {

	tinyxml2::XMLDocument document;
	if(document.LoadFile(filename)) abort();

	tinyxml2::XMLElement* element = document.FirstChildElement("layout");

	std::shared_ptr<glutpp::gui::layout> layout(new glutpp::gui::layout);
	layout->load_xml(element);

	layouts_[name] = layout;
}
int	neb::app::activate_scene(int name_window, int name_scene) {	
	NEBULA_DEBUG_0_FUNCTION;

	auto w = windows_.find(name_window);
	auto s = scenes_.find(name_scene);

	assert(w != windows_.end());
	assert(s != scenes_.end());

	w->second->set_scene(s->second);

	return 0;
}
int	neb::app::activate_layout(int name_window, int name_layout) {
	NEBULA_DEBUG_0_FUNCTION;

	auto w = windows_.find(name_window);
	auto l = layouts_.find(name_layout);

	assert(w != windows_.end());
	assert(l != layouts_.end());

	w->second->set_layout(l->second);

	return 0;
}
int neb::app::step(double time) {
	NEBULA_DEBUG_1_FUNCTION;

	std::shared_ptr<neb::scene::scene> scene;

	for(auto it = scenes_.begin(); it != scenes_.end(); ++it)
	{
		scene = it->second;

		assert(scene);

		scene->step(time);
	}

	return 0;
}
int	neb::app::loop() {
	NEBULA_DEBUG_1_FUNCTION;

	double time;
	int r;

	while(1)
	{	
		time = glfwGetTime();

		//printf("time = %f\n", time);

		// scene
		auto s = scenes_.begin();
		while(s != scenes_.end())
		{
			assert(s->second);
			s->second->step(time);
			s++;
		}	

		// windows		
		auto it = windows_.begin();
		while(it != windows_.end())
		{
			assert(it->second);
			r = it->second->step(time);

			if(r)
			{
				printf("erase\n");
				windows_.erase(it);
				break;
			}
			else
			{
				it++;
			}
		}

		glfwPollEvents();

	}

	return 0;
}
neb::scene::scene_shared neb::app::get_scene(int name) {
	NEBULA_DEBUG_1_FUNCTION;

	auto s = scenes_[name];

	assert(s);

	return s;
}
int neb::app::transmit_scenes(std::shared_ptr<neb::network::communicating> c) {
	NEBULA_DEBUG_0_FUNCTION;

	assert(c);

	int type = glutpp::network::type::SCENE_CREATE;
	
	for(auto it = scenes_.begin(); it != scenes_.end(); ++it) {
		auto s = it->second;
		assert(s);
		
		gal::network::message_shared msg(new gal::network::message);
		
		msg->write(&type, sizeof(int));
		
		glutpp::network::scene::create scene_create;
		
		scene_create.load(s);
		scene_create.write(msg);
		
		c->write(msg);
	}

	return 0;
}
void neb::app::send(gal::network::message::shared_t msg)  {
	NEBULA_DEBUG_1_FUNCTION;

	if(server_)
	{
		server_->write(msg);
	}
}

