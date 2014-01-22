#include <algorithm>

#include <glutpp/renderable.h>
#include <glutpp/window/desc.h>
#include <glutpp/window/window.h>
#include <glutpp/scene/desc.h>

#include <glutpp/network/message.h>

#include <neb/config.h>
#include <neb/control/rigid_body/control.h>
#include <neb/app.h>
#include <neb/network/message.h>
#include <neb/physics.h>

neb::app::app():
	flag_(0)
{
	NEBULA_DEBUG_0_FUNCTION;
}
void neb::app::f(unsigned int flag) {
	flag_ = flag;
}
unsigned int neb::app::f() {
	return flag_;
}
void neb::app::init() {
	NEBULA_DEBUG_0_FUNCTION;
}
glutpp::window::window_s neb::app::create_window(int w, int h, int x, int y, char const * title) {
	NEBULA_DEBUG_0_FUNCTION;

	glutpp::window::desc_s wd(new glutpp::window::desc(w,h,x,y,title));
	
	auto window = glutpp::__master.create_window<glutpp::window::window>(wd);
	
	printf("window use count = %i\n", (int)window.use_count());
	
	window->resize();
	
	windows_.push_back(window);

	printf("window use count = %i\n", (int)window.use_count());

	return window;
}
neb::scene::scene_s neb::app::load_scene_local(glutpp::scene::desc_s sd) {
	NEBULA_DEBUG_0_FUNCTION;

	neb::scene::scene_s scene(new neb::scene::scene(shared_from_this()));
	
	scene->init(sd);
	scene->user_type_ = neb::scene::scene::LOCAL;
	
	scenes_.push_back(scene);
	
	return scene;
}
neb::scene::scene_s neb::app::load_scene_remote(glutpp::scene::desc_s sd) {
	NEBULA_DEBUG_0_FUNCTION;

	neb::scene::scene_s scene(new neb::scene::scene(shared_from_this()));
	
	scene->init(sd);
	scene->user_type_ = neb::scene::scene::REMOTE;
	
	int i = scene->i();//desc_->raw_.i_;

	assert(i != -1);
	
	scenes_[i] = scene;
	
	return scene;
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

	for(auto it = scenes_.begin(); it != scenes_.end();)
	{
		scene = it->second;
		assert(scene);
		
		if(scene->all(glutpp::scene::flag::SHOULD_RELEASE))
		{
			scene->release();
			
			it = scenes_.erase(it);
		}
		else
		{
			scene->step(time);
			
			++it;	
		}
	}
	
	// windows
	for(auto it = windows_.begin(); it != windows_.end();)
	{
		auto w = it->second;
		assert(w);
		
		if(w->all(glutpp::window::window::flag::e::SHOULD_RELEASE))
		{
		
			printf("erase\n");
			it = windows_.erase(it);
		}
		else
		{
			w->step(time);
			
			it++;
		}
	}
	
	// timer
	timer_set_.step(time);
	
	return 0;
}
int	neb::app::loop() {
	NEBULA_DEBUG_1_FUNCTION;
	
	double time;
	
	while(!any(neb::app::flag::e::SHOULD_RELEASE))
	{	
		time = glfwGetTime();
		
		step(time);
		
		glfwPollEvents();
	}
	
	
	if(server_) server_->close();
	if(client_) client_->close();
	
	return 0;
}
void neb::app::set_should_release() {
	set(neb::app::flag::e::SHOULD_RELEASE);
}
glutpp::window::window_s neb::app::get_window(int i) {
	glutpp::window::window_s window;
	auto it = windows_.find(i);
	if(it != windows_.end())
	{
		return it->second;
	}
	
	return window;
}
neb::scene::scene_s neb::app::get_scene(int name) {
	NEBULA_DEBUG_1_FUNCTION;

	auto s = scenes_[name];

	assert(s);

	return s;
}
neb::scene::scene_s neb::app::get_scene(glutpp::scene::addr_s addr) {
	NEBULA_DEBUG_1_FUNCTION;
	
	assert(addr);

	auto vec = addr->get_vec();
	
	assert(vec->vec_.size() == 1);
	
	auto s = scenes_[vec->vec_.at(0)];
	
	assert(s);

	return s;
}
neb::actor::Base_s neb::app::get_actor(glutpp::actor::addr_s addr) {
	
	neb::actor::Base_s actor;
	
	auto scene = get_scene(addr->get_scene_addr());
	assert(scene);
	
	auto vec = addr->get_vec();
	if(!vec->vec_.empty())
	{
		actor = scene->get_actor(addr);
	}
	
	return actor;
}
int neb::app::transmit_scenes(std::shared_ptr<neb::network::communicating> c) {
	NEBULA_DEBUG_0_FUNCTION;

	assert(c);

	int type = glutpp::network::type::SCENE_CREATE;
	
	for(auto it = scenes_.begin(); it != scenes_.end(); ++it) {
		auto s = it->second;
		assert(s);
		
		gal::network::message_s msg(new gal::network::message);
		
		msg->write(&type, sizeof(int));
		
		glutpp::network::scene::create scene_create;
		
		scene_create.load(s);
		scene_create.write(msg);
		
		c->write(msg);
	}

	return 0;
}
void neb::app::reset_server(unsigned short port) {
	NEBULA_DEBUG_0_FUNCTION;
	server_.reset(new neb::network::server(shared_from_this(), port, 10));
}
void neb::app::reset_client(char const * addr, unsigned short port) {
	NEBULA_DEBUG_0_FUNCTION;
	client_.reset(new neb::network::client(shared_from_this(), addr, port));
	client_->start();
}
void neb::app::send_server(gal::network::message::shared_t msg)  {
	NEBULA_DEBUG_1_FUNCTION;
	
	if(server_)
	{
		server_->write(msg);
	}
	else
	{
		printf("WARNING: no server\n");
	}
}
void neb::app::send_client(gal::network::message::shared_t msg)  {
	NEBULA_DEBUG_1_FUNCTION;
	
	if(client_)
	{
		client_->write(msg);
	}
	else
	{
		printf("WARNING: no server\n");
	}
}
void neb::app::recv_scene_create(gal::network::message_s msg) {
	
}
void neb::app::recv_actor_create(gal::network::message_s msg) {
	
}
void neb::app::recv_actor_update(gal::network::message_s msg) {

}
void neb::app::recv_actor_event(gal::network::message_s msg) {
	
	glutpp::network::actor::event actor_event;
	actor_event.read(msg);

	auto actor = get_actor(actor_event.get_addr());
	assert(actor);
	auto scene = actor->get_scene();
	assert(scene);
	
	int type = actor_event.get_event()->type_;

	switch(type)
	{
		case glutpp::actor::type_event::FIRE:
			scene->fire(actor);
			break;
		default:
			printf("DEBUG: unknown event type %i\n", type);
			break;
	}
}
void neb::app::recv_control_create(gal::network::message_s msg) {

}
void neb::app::recv_control_update(gal::network::message_s msg) {

	neb::network::control::rigid_body::update control_update;
	control_update.read(msg);

	auto actor = get_actor(control_update.get_addr());
	auto rigidbody = actor->to_rigid_body();

	if(rigidbody)
	{
		auto control = rigidbody->control_;
		if(control)
		{
			control->raw_ = *(control_update.get_raw());

			control->print();
		}
		else
		{
			printf("control not found\n");
		}
	}
	else
	{
		printf("actor not found\n");
	}
}





