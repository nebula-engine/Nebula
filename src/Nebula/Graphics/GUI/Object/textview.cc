#include <stdio.h>
#include <string.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <Nebula/free.hh>
#include <Nebula/Graphics/GUI/Object/textview.hh>

Neb::Graphics::GUI::Object::textview::textview() {
}
void	Neb::Graphics::GUI::Object::textview::clear_label() {
	label_.clear();
}
void	Neb::Graphics::GUI::Object::textview::draw() {
	//printf("%s\n",__PRETTY_FUNCTION__);

	float sx = 1.0/600.0;
	float sy = 1.0/600.0;

	draw_quad(x_, y_, w_, h_, bg_color_);
	draw_text(x_, y_, sx, sy, font_color_, label_);
}
int	Neb::Graphics::GUI::Object::textview::mouse_button_fun(int button, int action, int mods) {
	printf("%s\n", __PRETTY_FUNCTION__);

	return Neb::Graphics::GUI::Object::Base::mouse_button_fun(button, action, mods);
}
int	Neb::Graphics::GUI::Object::textview::key_fun(int key, int scancode, int action, int mods) {
	printf("%s\n", __PRETTY_FUNCTION__);
	return 0;
}




