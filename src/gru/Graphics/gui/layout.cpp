#include <tinyxml2.h>

#include <string>
#include <algorithm>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <gru/Graphics/window/window.hpp>
#include <gru/renderable.hpp>
#include <gru/Graphics/gui/object/object_factory.hpp>
#include <gru/Graphics/gui/object/object.hpp>
#include <gru/Graphics/gui/object/edittext.hpp>

#include <gru/Graphics/gui/layout.hpp>




glutpp::gui::layout::layout()
{

}
void glutpp::gui::layout::init(glutpp::renderable_s renderable)
{
	//jess::clog << NEB_FUNCSIG << std::endl;
	assert(renderable);
	renderable_ = renderable;
}
glutpp::window::window_s glutpp::gui::layout::get_window()
{
	assert(!renderable_.expired());

	return renderable_.lock()->getWindow();
}
/*
void glutpp::gui::layout::load_xml(tinyxml2::XMLElement* element)
{
	assert(element);
	tinyxml2::XMLElement* e = element->FirstChildElement("object");
	while(e != NULL){
		create_object(e);
		e = e->NextSiblingElement("object");
	}
}*/
/*
void glutpp::gui::layout::create_object(tinyxml2::XMLElement* element) {

	assert(element);

	auto object = glutpp::master::Global()->object_factory_->create(element);

	objects_.push_back(object);
}*/
void glutpp::gui::layout::render(double time) {
	//auto p = glutpp::master::Global()->use_program(glutpp::program_name::e::TEXT);

	//Restore other states
	//glDisable(GL_LIGHTING);
	//glDisable(GL_ALPHA_TEST);

	//Set matrices for ortho
	//glMatrixMode(GL_PROJECTION);
	//glLoadMatrixf(ortho_);
	//gluOrtho2D(-1.0f, 1.0f, -1.0f, 1.0f);

	//glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();

	draw();
}
void glutpp::gui::layout::draw() {
	//jess::clog << NEB_FUNCSIG << std::endl;
	//jess::clog << "objects_.size()=" << objects_.map_.size() << std::endl;

	for(auto it = objects_.map_.begin(); it != objects_.map_.end(); ++it) {
		it->second->draw();
	}
}
void glutpp::gui::layout::connect() {
	printf("%s\n", __PRETTY_FUNCTION__);

	glutpp::window::window_s w = get_window();

	conns_.key_fun_ = w->sig_.key_fun_.connect(
			std::bind(&glutpp::gui::layout::key_fun,
				this,
				std::placeholders::_1,
				std::placeholders::_2,
				std::placeholders::_3,
				std::placeholders::_4
				));

	conns_.mouse_button_fun_ = w->sig_.mouse_button_fun_.connect(
			std::bind(&glutpp::gui::layout::mouse_button_fun,
				this,
				std::placeholders::_1,
				std::placeholders::_2,
				std::placeholders::_3
				));

}
int glutpp::gui::layout::key_fun(int key, int scancode, int action, int mode) {
	return 0;
}
int glutpp::gui::layout::mouse_button_fun(int button, int action, int mods) {
	printf("%s\n", __PRETTY_FUNCTION__);

	switch(action)
	{
		case GLFW_PRESS:
			switch(button)
			{
				case GLFW_MOUSE_BUTTON_LEFT:
					search(button, action, mods);
					break;
			}
			break;
		default:
			return 0;
	}
	
	return 0;
}
int glutpp::gui::layout::search(int button, int action, int mods) {
	printf("%s\n", __PRETTY_FUNCTION__);

	double x, y;
	int w, h;
	glfwGetCursorPos(get_window()->window_, &x, &y);
	glfwGetWindowSize(get_window()->window_, &w, &h);

	printf("%f %f %i %i\n", x, y, w, h);

	x = x / (float)w * 2.0 - 1.0;
	y = y / (float)h * 2.0 - 1.0;

	printf("%f %f\n", x, y);

	for(auto it = objects_.map_.begin(); it != objects_.map_.end(); ++it) {

		//auto o = (*it).second;
		
		printf("object %f %f %f %f\n",
				it->second->data_.x_,
				it->second->data_.y_,
				it->second->data_.w_,
				it->second->data_.h_);	
		
		if(x <   it->second->data_.x_) continue;
		if(x > ( it->second->data_.x_ + it->second->data_.w_)) continue;
		if(y >  -it->second->data_.y_) continue;
		if(y < (-it->second->data_.y_ - it->second->data_.h_)) continue;

		return it->second->mouse_button_fun(button, action, mods);
	}

	return 0;
}







