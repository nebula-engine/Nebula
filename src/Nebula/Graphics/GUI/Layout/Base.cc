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
void		Neb::Graphics::GUI::Layout::Base::draw(sp::shared_ptr<Neb::Graphics::Context::Base> context) {
	//jess::clog << NEB_FUNCSIG << std::endl;
	//jess::clog << "objects_.size()=" << objects_.map_.size() << std::endl;
	
	typedef Neb::Graphics::GUI::Object::Util::Parent O;
	
	O::map_.for_each<0>([] (O::map_type::iterator<0> it) {
		auto object = sp::dynamic_pointer_cast<Neb::Graphics::GUI::Object::Base>(it->ptr_);
		assert(object);
		object->draw();
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
	
	typedef Neb::Graphics::GUI::Object::Util::Parent O;
	
	sp::shared_ptr<Neb::Graphics::GUI::Object::Base> object;
	sp::shared_ptr<Neb::Graphics::GUI::Object::Base> objecttmp;

	O::map_.for_each_int<0>([&] (O::map_type::iterator<0> it) {
		objecttmp = sp::dynamic_pointer_cast<Neb::Graphics::GUI::Object::Base>(it->ptr_);
		assert(objecttmp);
		printf("object %f %f %f %f\n",
				objecttmp->x_,
				objecttmp->y_,
				objecttmp->w_,
				objecttmp->h_);	
		
		if(x <   objecttmp->x_) return O::map_type::CONTINUE;
		if(x > ( objecttmp->x_ + objecttmp->w_)) return O::map_type::CONTINUE;
		if(y >  -objecttmp->y_) return O::map_type::CONTINUE;
		if(y < (-objecttmp->y_ - objecttmp->h_)) return O::map_type::CONTINUE;
		
		object = objecttmp;
		
		return O::map_type::BREAK;
	});
	
	if(object) return object->mouse_button_fun(button, action, mods);
	
	return 0;
}







