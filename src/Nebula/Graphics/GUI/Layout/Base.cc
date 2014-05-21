#include <tinyxml2.h>

#include <string>
#include <algorithm>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <Nebula/Types.hh>
#include <Nebula/Graphics/Window/Base.hh>
#include <Nebula/Graphics/Context/Base.hh>
#include <Nebula/Graphics/GUI/Object/Base.hh>
#include <Nebula/Graphics/GUI/Object/edittext.hh>

#include <Nebula/Graphics/GUI/Layout/Base.hh>


Neb::Graphics::GUI::Layout::Base::Base() {
}
Neb::Graphics::GUI::Layout::Base::Base(Neb::Graphics::GUI::Layout::Util::Parent_s parent): parent_(parent) {
}
void Neb::Graphics::GUI::Layout::Base::init() {
	//jess::clog << NEB_FUNCSIG << std::endl;
}
/*
void Neb::Graphics::GUI::Layout::Base::load_xml(tinyxml2::XMLElement* element)
{
	assert(element);
	tinyxml2::XMLElement* e = element->FirstChildElement("object");
	while(e != NULL){
		create_object(e);
		e = e->NextSiblingElement("object");
	}
}*/
/*
void Neb::Graphics::GUI::Layout::Base::create_object(tinyxml2::XMLElement* element) {

	assert(element);

	auto object = Neb::master::Global()->object_factory_->create(element);

	objects_.push_back(object);
}*/
void Neb::Graphics::GUI::Layout::Base::render(double time) {
	//auto p = Neb::master::Global()->use_program(Neb::program_name::e::TEXT);

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
void Neb::Graphics::GUI::Layout::Base::draw() {
	//jess::clog << NEB_FUNCSIG << std::endl;
	//jess::clog << "objects_.size()=" << objects_.map_.size() << std::endl;
	
	typedef Neb::Util::Parent<Neb::Graphics::GUI::Object::Base> O;
	
	O::map_.for_each([] (O::map_type::const_iterator it) {
		it->second.ptr_->draw();
	});

}
void Neb::Graphics::GUI::Layout::Base::connect() {
	printf("%s\n", __PRETTY_FUNCTION__);
	
	auto window = parent_->getWindow();
	assert(window);
	
	conns_.key_fun_ = window->sig_.key_fun_.connect(
			std::bind(&Neb::Graphics::GUI::Layout::Base::key_fun,
				this,
				std::placeholders::_1,
				std::placeholders::_2,
				std::placeholders::_3,
				std::placeholders::_4
				));
	
	conns_.mouse_button_fun_ = window->sig_.mouse_button_fun_.connect(
			std::bind(&Neb::Graphics::GUI::Layout::Base::mouse_button_fun,
				this,
				std::placeholders::_1,
				std::placeholders::_2,
				std::placeholders::_3
				));

}
int Neb::Graphics::GUI::Layout::Base::key_fun(int key, int scancode, int action, int mode) {
	return 0;
}
int Neb::Graphics::GUI::Layout::Base::mouse_button_fun(int button, int action, int mods) {
	printf("%s\n", __PRETTY_FUNCTION__);

	switch(action) {
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
int Neb::Graphics::GUI::Layout::Base::search(int button, int action, int mods) {
	printf("%s\n", __PRETTY_FUNCTION__);

	auto window = parent_->getWindow();
	assert(window);

	double x, y;
	int w, h;
	glfwGetCursorPos(window->window_, &x, &y);
	glfwGetWindowSize(window->window_, &w, &h);

	printf("%f %f %i %i\n", x, y, w, h);

	x = x / (float)w * 2.0 - 1.0;
	y = y / (float)h * 2.0 - 1.0;

	printf("%f %f\n", x, y);
	
	typedef Neb::Util::Parent<Neb::Graphics::GUI::Object::Base> O;
	
	Neb::Graphics::GUI::Object::Base_s object;
	
	O::map_.for_each_int([&] (O::map_type::const_iterator it) {
		
		printf("object %f %f %f %f\n",
				it->second.ptr_->x_,
				it->second.ptr_->y_,
				it->second.ptr_->w_,
				it->second.ptr_->h_);	
		
		if(x <   it->second.ptr_->x_) return O::map_type::CONTINUE;
		if(x > ( it->second.ptr_->x_ + it->second.ptr_->w_)) return O::map_type::CONTINUE;
		if(y >  -it->second.ptr_->y_) return O::map_type::CONTINUE;
		if(y < (-it->second.ptr_->y_ - it->second.ptr_->h_)) return O::map_type::CONTINUE;
		
		object = it->second.ptr_;
		
		return O::map_type::BREAK;
	});
	
	if(object) return object->mouse_button_fun(button, action, mods);
	
	return 0;
}







