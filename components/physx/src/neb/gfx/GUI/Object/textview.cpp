#include <stdio.h>
#include <string.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <neb/gfx/free.hpp>
#include <neb/gfx/gui/object/textview.hh>

neb::gfx::gui::object::textview::textview() {
}
void	neb::gfx::gui::object::textview::clear_label() {
	label_.clear();
}
void	neb::gfx::gui::object::textview::draw(std::shared_ptr<neb::gfx::glsl::program::base> p) {
	//printf("%s\n",__PRETTY_FUNCTION__);

	float sx = 1.0/600.0;
	float sy = 1.0/600.0;

	draw_quad(p, x_, y_, w_, h_, bg_color_);
	draw_text(p, x_, y_, sx, sy, font_color_, label_);
}
int	neb::gfx::gui::object::textview::mouseButtonFun(
		std::shared_ptr<neb::core::input::source> const & src,
		int button,
		int action,
		int mods)
{
	printf("%s\n", __PRETTY_FUNCTION__);

	return neb::gfx::gui::object::base::mouseButtonFun(src, button, action, mods);
}
int	neb::gfx::gui::object::textview::keyFun(
		std::shared_ptr<neb::core::input::source> const & src,
		int key,
		int scancode,
		int action,
		int mods)
{
	printf("%s\n", __PRETTY_FUNCTION__);
	return 0;
}




