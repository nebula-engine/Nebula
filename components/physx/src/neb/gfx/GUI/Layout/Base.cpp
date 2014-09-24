
#include <string>
#include <algorithm>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <gal/log/log.hpp>

#include <neb/core/util/debug.hpp>
#include <neb/core/util/decl.hpp>

#include <neb/core/input/source.hpp>

#include <neb/gfx/Context/Base.hh>
#include <neb/gfx/gui/object/Base.hh>
#include <neb/gfx/gui/object/edittext.hh>
#include <neb/gfx/gui/object/terminal.hh>
#include <neb/gfx/gui/layout/base.hpp>
#include <neb/gfx/gui/layout/util/parent.hpp>
#include <neb/gfx/util/log.hpp>

neb::gfx::gui::layout::base::base()
{
	LOG(lg, neb::gfx::sl, debug) << __PRETTY_FUNCTION__;
}
void neb::gfx::gui::layout::base::init(parent_t * const & p)
{
	LOG(lg, neb::gfx::sl, debug) << __PRETTY_FUNCTION__;

	setParent(p);
}
void		neb::gfx::gui::layout::base::step(gal::etc::timestep const & ts)
{
	LOG(lg, neb::gfx::sl, debug) << __PRETTY_FUNCTION__;

}
void			neb::gfx::gui::layout::base::draw(neb::gfx::RenderDesc const & desc)
{	
	LOG(lg, neb::gfx::sl, debug) << __PRETTY_FUNCTION__;

	typedef neb::gfx::gui::object::util::parent O;

	auto lamb = [&] (O::map_type::pointer p) {
		auto object = std::dynamic_pointer_cast<neb::gfx::gui::object::base>(p);
		assert(object);
		object->draw(desc);
	};

	O::map_.for_each(lamb);

}
void			neb::gfx::gui::layout::base::connect(std::shared_ptr<neb::core::input::source> const & src)
{
	LOG(lg, neb::gfx::sl, debug) << __PRETTY_FUNCTION__;

	connectKeyFun(src, 10);
	connectCharFun(src, 10);
	connectMouseButtonFun(src, 10);
}
int			neb::gfx::gui::layout::base::keyFun(
		std::shared_ptr<neb::core::input::source> const & src,
		int key,
		int scancode,
		int action,
		int mode)
{
	LOG(lg, neb::gfx::sl, debug) << __PRETTY_FUNCTION__;

	typedef neb::gfx::gui::object::util::parent O;

	//O::map_.for_each_int<0>([&] (O::map_type::iterator<0> it) {
	for(O::map_type::iterator it = O::map_.begin(); it != O::map_.end(); ++it) {
		auto object = std::dynamic_pointer_cast<neb::gfx::gui::object::base>(it->second.ptr_);
		assert(object);

		if(object->keyFun(src, key, scancode, action, mode)) return 1;
	};

	return 0;
}
int			neb::gfx::gui::layout::base::charFun(
		std::shared_ptr<neb::core::input::source> const & window,
		unsigned int codepoint)
{
	LOG(lg, neb::gfx::sl, debug) << __PRETTY_FUNCTION__;

	typedef neb::gfx::gui::object::util::parent O;

	for(O::map_type::iterator it = O::map_.begin(); it != O::map_.end(); ++it) {
		auto object = dynamic_pointer_cast<neb::gfx::gui::object::base>(it->second.ptr_);
		assert(object);

		if(object->charFun(window, codepoint)) return 1;
	};

	return 0;
}
int			neb::gfx::gui::layout::base::mouseButtonFun(
		std::shared_ptr<neb::core::input::source> const & src,
		int button,
		int action,
		int mods)
{

	LOG(lg, neb::gfx::sl, debug) << __PRETTY_FUNCTION__;

	assert(src);

	switch(action) {
		case GLFW_PRESS:
			switch(button)
			{
				case GLFW_MOUSE_BUTTON_LEFT:
					search(src, button, action, mods);
					break;
			}
			break;
		default:
			return 0;
	}

	return 0;
}
int			neb::gfx::gui::layout::base::search(
		std::shared_ptr<neb::core::input::source> const & src,
		int button,
		int action,
		int mods)
{

	LOG(lg, neb::gfx::sl, debug) << __PRETTY_FUNCTION__;

	assert(src);

	/*
	double x, y;
	int w, h;
	glfwGetCursorPos(window->window_, &x, &y);
	glfwGetWindowSize(window->window_, &w, &h);

	printf("%f %f %i %i\n", x, y, w, h);

	x = x / (float)w * 2.0 - 1.0;
	y = y / (float)h * 2.0 - 1.0;

	printf("%f %f\n", x, y);
	*/
	
	glm::vec2 c = src->getCursorPosNDC();
	
	typedef neb::gfx::gui::object::util::parent O;

	std::shared_ptr<neb::gfx::gui::object::base> object;
	std::shared_ptr<neb::gfx::gui::object::base> objecttmp;

	auto lamb = [&] (O::map_type::pointer p) {
		objecttmp = std::dynamic_pointer_cast<neb::gfx::gui::object::base>(p);
		assert(objecttmp);
		printf("object %f %f %f %f\n",
				objecttmp->x_,
				objecttmp->y_,
				objecttmp->w_,
				objecttmp->h_);	

		if(c.x <   objecttmp->x_) return O::map_type::CONTINUE;
		if(c.x > ( objecttmp->x_ + objecttmp->w_)) return O::map_type::CONTINUE;
		if(c.y >  -objecttmp->y_) return O::map_type::CONTINUE;
		if(c.y < (-objecttmp->y_ - objecttmp->h_)) return O::map_type::CONTINUE;

		object = objecttmp;

		return O::map_type::BREAK;
	};

	O::map_.for_each_int(lamb);

	if(object) return object->mouseButtonFun(src, button, action, mods);

	return 0;
}
weak_ptr<neb::gfx::gui::object::terminal>		neb::gfx::gui::layout::base::createObjectTerminal() {

	return neb::gfx::gui::object::util::parent::create<neb::gfx::gui::object::terminal>();

	//auto term = sp::make_shared<neb::gfx::gui::object::terminal>();
	//insert(term);
	//term->init();
	//return term;
}


