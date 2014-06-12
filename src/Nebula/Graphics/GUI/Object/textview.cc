#include <stdio.h>
#include <string.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <Nebula/free.hh>
#include <Nebula/Graphics/GUI/Object/textview.hh>

neb::gfx::GUI::Object::textview::textview() {
}
void	neb::gfx::GUI::Object::textview::clear_label() {
	label_.clear();
}
void	neb::gfx::GUI::Object::textview::draw(sp::shared_ptr<neb::glsl::program> p) {
	//printf("%s\n",__PRETTY_FUNCTION__);

	float sx = 1.0/600.0;
	float sy = 1.0/600.0;
	
	draw_quad(p, x_, y_, w_, h_, bg_color_);
	draw_text(p, x_, y_, sx, sy, font_color_, label_);
}
int	neb::gfx::GUI::Object::textview::mouse_button_fun(sp::shared_ptr<neb::gfx::Window::Base> const & window, int button, int action, int mods) {
	printf("%s\n", __PRETTY_FUNCTION__);

	return neb::gfx::GUI::Object::Base::mouse_button_fun(window, button, action, mods);
}
int	neb::gfx::GUI::Object::textview::key_fun(sp::shared_ptr<neb::gfx::Window::Base> const & window, int key, int scancode, int action, int mods) {
	printf("%s\n", __PRETTY_FUNCTION__);
	return 0;
}




