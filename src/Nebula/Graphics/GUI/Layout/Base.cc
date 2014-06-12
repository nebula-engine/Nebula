
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


neb::gfx::GUI::Layout::Base::Base() {
}
neb::gfx::GUI::Layout::Base::Base(sp::shared_ptr<neb::gfx::GUI::Layout::Util::Parent> parent): parent_(parent) {
}
void neb::gfx::GUI::Layout::Base::init() {
	//jess::clog << NEB_FUNCSIG << std::endl;
}
/*
void neb::gfx::GUI::Layout::Base::load_xml(tinyxml2::XMLElement* element)
{
	assert(element);
	tinyxml2::XMLElement* e = element->FirstChildElement("object");
	while(e != NULL){
		create_object(e);
		e = e->NextSiblingElement("object");
	}
}*/
/*
void neb::gfx::GUI::Layout::Base::create_object(tinyxml2::XMLElement* element) {

	assert(element);

	auto object = neb::master::Global()->object_factory_->create(element);

	objects_.push_back(object);
}*/
void		neb::gfx::GUI::Layout::Base::step(neb::core::TimeStep const & ts) {
}
void		neb::gfx::GUI::Layout::Base::draw(sp::shared_ptr<neb::gfx::Context::Base> context) {
	//jess::clog << NEB_FUNCSIG << std::endl;
	//jess::clog << "objects_.size()=" << objects_.map_.size() << std::endl;
	
	typedef neb::gfx::GUI::Object::Util::Parent O;
	
	O::map_.for_each<0>([] (O::map_type::iterator<0> it) {
		auto object = sp::dynamic_pointer_cast<neb::gfx::GUI::Object::Base>(it->ptr_);
		assert(object);
		object->draw();
	});

}
void neb::gfx::GUI::Layout::Base::connect(sp::shared_ptr<neb::gfx::Window::Base> const & window) {
	printf("%s\n", __PRETTY_FUNCTION__);
	
	conns_.key_fun_ = window->sig_.key_fun_.connect(
			::std::bind(&neb::gfx::GUI::Layout::Base::key_fun,
				this,
				::std::placeholders::_1,
				::std::placeholders::_2,
				::std::placeholders::_3,
				::std::placeholders::_4,
				::std::placeholders::_5
				));
	
	conns_.mouse_button_fun_ = window->sig_.mouse_button_fun_.connect(
			::std::bind(&neb::gfx::GUI::Layout::Base::mouse_button_fun,
				this,
				::std::placeholders::_1,
				::std::placeholders::_2,
				::std::placeholders::_3,
				::std::placeholders::_4
				));

}
int neb::gfx::GUI::Layout::Base::key_fun(sp::shared_ptr<neb::gfx::Window::Base> const & window, int key, int scancode, int action, int mode) {
	printf("%s\n", __PRETTY_FUNCTION__);
	
	typedef neb::gfx::GUI::Object::Util::Parent O;
	
	//O::map_.for_each_int<0>([&] (O::map_type::iterator<0> it) {
	for(O::map_type::iterator<0> it = O::map_.begin(); it != O::map_.end(); ++it) {
		auto object = sp::dynamic_pointer_cast<neb::gfx::GUI::Object::Base>(it->ptr_);
		assert(object);
		
		if(object->key_fun(window, key, scancode, action, mode)) return 1;
	};
	
	return 0;
}
int neb::gfx::GUI::Layout::Base::mouse_button_fun(sp::shared_ptr<neb::gfx::Window::Base> const & window, int button, int action, int mods) {
	printf("%s\n", __PRETTY_FUNCTION__);

	assert(window);

	switch(action) {
		case GLFW_PRESS:
			switch(button)
			{
				case GLFW_MOUSE_BUTTON_LEFT:
					search(window, button, action, mods);
					break;
			}
			break;
		default:
			return 0;
	}

	return 0;
}
int neb::gfx::GUI::Layout::Base::search(sp::shared_ptr<neb::gfx::Window::Base> const & window, int button, int action, int mods) {
	printf("%s\n", __PRETTY_FUNCTION__);

	assert(window);

	double x, y;
	int w, h;
	glfwGetCursorPos(window->window_, &x, &y);
	glfwGetWindowSize(window->window_, &w, &h);

	printf("%f %f %i %i\n", x, y, w, h);

	x = x / (float)w * 2.0 - 1.0;
	y = y / (float)h * 2.0 - 1.0;

	printf("%f %f\n", x, y);

	typedef neb::gfx::GUI::Object::Util::Parent O;

	sp::shared_ptr<neb::gfx::GUI::Object::Base> object;
	sp::shared_ptr<neb::gfx::GUI::Object::Base> objecttmp;

	O::map_.for_each_int<0>([&] (O::map_type::iterator<0> it) {
			objecttmp = sp::dynamic_pointer_cast<neb::gfx::GUI::Object::Base>(it->ptr_);
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

	if(object) return object->mouse_button_fun(window, button, action, mods);

	return 0;
}







