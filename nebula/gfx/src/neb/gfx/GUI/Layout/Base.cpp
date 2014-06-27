
#include <string>
#include <algorithm>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <gal/log/log.hpp>

#include <neb/debug.hh>
#include <neb/util/decl.hpp>
#include <neb/gfx/window/Base.hh>
#include <neb/gfx/Context/Base.hh>
#include <neb/gfx/GUI/Object/Base.hh>
#include <neb/gfx/GUI/Object/edittext.hh>

#include <neb/gfx/GUI/Layout/Base.hh>

neb::gfx::gui::layout::base::base(sp::shared_ptr<neb::gfx::gui::layout::util::parent> parent): parent_(parent) {

	if(DEBUG_NEB) BOOST_LOG_CHANNEL_SEV(lg, "neb gfx free", debug) << __PRETTY_FUNCTION__;

}
void neb::gfx::gui::layout::base::init() {

	if(DEBUG_NEB) BOOST_LOG_CHANNEL_SEV(lg, "neb gfx free", debug) << __PRETTY_FUNCTION__;
	//jess::clog << NEB_FUNCSIG << std::endl;
}
void		neb::gfx::gui::layout::base::step(gal::std::timestep const & ts) {
		if(DEBUG_NEB) BOOST_LOG_CHANNEL_SEV(lg, "neb gfx free", debug) << __PRETTY_FUNCTION__;

}
void		neb::gfx::gui::layout::base::draw(sp::shared_ptr<neb::gfx::context::base> context, sp::shared_ptr<neb::glsl::program> p) {
	
	if(DEBUG_NEB) BOOST_LOG_CHANNEL_SEV(lg, "neb gfx free", debug) << __PRETTY_FUNCTION__;
	
	typedef neb::gfx::gui::object::util::parent O;
	
	O::map_.for_each<0>([&] (O::map_type::iterator<0> it) {
		auto object = sp::dynamic_pointer_cast<neb::gfx::gui::object::base>(it->ptr_);
		assert(object);
		object->draw(p);
	});

}
void neb::gfx::gui::layout::base::connect(sp::shared_ptr<neb::gfx::window::base> const & window) {
	
	if(DEBUG_NEB) BOOST_LOG_CHANNEL_SEV(lg, "neb gfx free", debug) << __PRETTY_FUNCTION__;
	
	conns_.key_fun_ = window->sig_.key_fun_.connect(
			10,
			::std::bind(&neb::gfx::gui::layout::base::key_fun,
				this,
				::std::placeholders::_1,
				::std::placeholders::_2,
				::std::placeholders::_3,
				::std::placeholders::_4,
				::std::placeholders::_5
				));

	conns_.mouse_button_fun_ = window->sig_.mouse_button_fun_.connect(
			10,
			::std::bind(&neb::gfx::gui::layout::base::mouse_button_fun,
				this,
				::std::placeholders::_1,
				::std::placeholders::_2,
				::std::placeholders::_3,
				::std::placeholders::_4
				));

}
int neb::gfx::gui::layout::base::key_fun(sp::shared_ptr<neb::gfx::window::base> const & window, int key, int scancode, int action, int mode) {
	
	if(DEBUG_NEB) BOOST_LOG_CHANNEL_SEV(lg, "neb gfx free", debug) << __PRETTY_FUNCTION__;

	typedef neb::gfx::gui::object::util::parent O;

	//O::map_.for_each_int<0>([&] (O::map_type::iterator<0> it) {
	for(O::map_type::iterator<0> it = O::map_.begin(); it != O::map_.end(); ++it) {
		auto object = sp::dynamic_pointer_cast<neb::gfx::gui::object::base>(it->ptr_);
		assert(object);

		if(object->key_fun(window, key, scancode, action, mode)) return 1;
	};

	return 0;
}
int neb::gfx::gui::layout::base::mouse_button_fun(sp::shared_ptr<neb::gfx::window::base> const & window, int button, int action, int mods) {

	if(DEBUG_NEB) BOOST_LOG_CHANNEL_SEV(lg, "neb gfx free", debug) << __PRETTY_FUNCTION__;

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
int neb::gfx::gui::layout::base::search(sp::shared_ptr<neb::gfx::window::base> const & window, int button, int action, int mods) {
	
	if(DEBUG_NEB) BOOST_LOG_CHANNEL_SEV(lg, "neb gfx free", debug) << __PRETTY_FUNCTION__;

	assert(window);

	double x, y;
	int w, h;
	glfwGetCursorPos(window->window_, &x, &y);
	glfwGetWindowSize(window->window_, &w, &h);

	printf("%f %f %i %i\n", x, y, w, h);

	x = x / (float)w * 2.0 - 1.0;
	y = y / (float)h * 2.0 - 1.0;

	printf("%f %f\n", x, y);

	typedef neb::gfx::gui::object::util::parent O;

	sp::shared_ptr<neb::gfx::gui::object::base> object;
	sp::shared_ptr<neb::gfx::gui::object::base> objecttmp;

	O::map_.for_each_int<0>([&] (O::map_type::iterator<0> it) {
			objecttmp = sp::dynamic_pointer_cast<neb::gfx::gui::object::base>(it->ptr_);
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







