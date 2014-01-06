#include <algorithm>

#include <glutpp/renderable.h>
#include <glutpp/window/desc.h>
#include <glutpp/window/window.h>
#include <glutpp/scene/desc.h>

#include <neb/config.h>
#include <neb/app.h>
#include <neb/physics.h>
#include <neb/packet/packet.h>

neb::app::app() {
}
void	neb::app::init() {
}
glutpp::window::window_shared neb::app::create_window(int w, int h, int x, int y, char const * title) {
	
	glutpp::window::desc_shared wd(new glutpp::window::desc(w,h,x,y,title));
	
	auto window = glutpp::__master.create_window<glutpp::window::window>(wd);
	
	window->resize();
	
	windows_.push_back(window);
	
	return window;
}
void neb::app::load_scene(glutpp::scene::desc_shared sd) {
	
	// scene
	neb::scene::scene_shared scene(new neb::scene::scene(shared_from_this(), sd));
	
	scene->user_type_ = neb::scene::scene::LOCAL;
	scene->init();
	
	if(sd->raw_.i_ == -1)
	{
		scenes_.push_back(scene);
	}
	else
	{
		scenes_[scene->desc_->raw_.i_] = scene;
	}
	
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
	printf("%s\n", __PRETTY_FUNCTION__);
	
	auto w = windows_.find(name_window);
	auto s = scenes_.find(name_scene);
	
	assert(w != windows_.end());
	assert(s != scenes_.end());
	
	w->second->set_scene(s->second);
	
	return 0;
}
int	neb::app::activate_layout(int name_window, int name_layout) {
	printf("%s\n", __PRETTY_FUNCTION__);

	auto w = windows_.find(name_window);
	auto l = layouts_.find(name_layout);
	
	assert(w != windows_.end());
	assert(l != layouts_.end());
	
	w->second->set_layout(l->second);
	
	return 0;
}
int neb::app::step(double time) {

	printf("%s\n", __PRETTY_FUNCTION__);
	
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
	
	auto s = scenes_[name];
	
	assert(s);
	
	return s;
}
int neb::app::transmit_scenes(std::shared_ptr<neb::network::communicating> c) {
	
	NEBULA_DEBUG_0_FUNCTION;
	
	assert(c);
	
	gal::network::message::shared_t msg;
	
	for(auto it = scenes_.begin(); it != scenes_.end(); ++it)
	{
		auto s = it->second;
		assert(s);
		
		msg = s->serialize();
		
		c->write(msg);
	}
	
	return 0;
}
void neb::app::send(gal::network::message::shared_t msg)  {
	
	if(server_)
	{
		server_->write(msg);
	}
}

