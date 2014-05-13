#include <stdio.h>
#include <string.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <Nebula/free.hpp>
#include <Nebula/Graphics/gui/object/textview.hpp>

Neb::gui::object::textview::textview()
{
}
void	Neb::gui::object::textview::clear_label()
{
	data_.label_.clear();
}
void	Neb::gui::object::textview::draw()
{
	//printf("%s\n",__PRETTY_FUNCTION__);

	float sx = 1.0/600.0;
	float sy = 1.0/600.0;

	draw_quad(data_.x_, data_.y_, data_.w_, data_.h_, data_.bg_color_);
	draw_text(data_.x_, data_.y_, sx, sy, data_.font_color_, data_.label_);
}
int	Neb::gui::object::textview::mouse_button_fun(int button, int action, int mods) {
	printf("%s\n", __PRETTY_FUNCTION__);

	return Neb::gui::object::object::mouse_button_fun(button, action, mods);
}
int	Neb::gui::object::textview::key_fun(int key, int scancode, int action, int mods)
{
	printf("%s\n", __PRETTY_FUNCTION__);
	return 0;
}




