#include <algorithm>

#include <glutpp/renderable.h>
#include <glutpp/window.h>

#include <neb/config.h>
#include <neb/app.h>
#include <neb/physics.h>
#include <neb/packet/packet.h>

neb::app::app() {
}
void	neb::app::init() {
}
void neb::app::create_window(int name, int w, int h, int x, int y, char const * title) {

	windows_[name] = glutpp::__master.create_window<glutpp::window>(w,h,x,y,title);
}
void neb::app::load_scene(int name, scene::desc* sd) {
	
	// scene
	auto scene = neb::__physics.create_scene(sd);
	
	scene->desc_ = sd;
	
	scene->user_type_ = neb::scene::scene::LOCAL;
	
	scene->init();
	
	scenes_[name] = scene;
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
int	neb::app::prepare() {
	
	for(auto it = windows_.begin(); it != windows_.end(); ++it)
	{
		if(it->second) it->second->prepare();
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
int neb::app::transmit_scenes(std::shared_ptr<neb::network::communicating> c) {
	
	NEBULA_DEBUG_0_FUNCTION;
	
	assert(c);
	
	gal::network::message::shared_t msg;
	
	for(auto it = scenes_.begin(); it != scenes_.end(); ++it)
	{
		msg.reset(new gal::network::message);
		
		auto s = it->second;
		assert(s);
		
		msg = s->serialize();
		
		c->write(msg);
	}
	
	NEBULA_DEBUG_0_FUNCTION;

	return 0;
}





