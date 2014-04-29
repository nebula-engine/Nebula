#include <string.h>
#include <algorithm>

#include <gru/gui/object/object.hpp>

glutpp::gui::object::Data::Data():
	x_(0.0),
	y_(0.0),
	w_(0.3),
	h_(0.3),
	font_color_(gru::Color::magenta<float>()),
	bg_color_(0,0,0,0)
{}



glutpp::gui::object::object::object()
{
}
void glutpp::gui::object::object::i(int ni) {
	i_ = ni;
}
glutpp::window::window_s get_window() {
	printf("%s\n", __PRETTY_FUNCTION__);
	printf("not yet supported");
	abort();
}
int	glutpp::gui::object::object::mouse_button_fun(int,int,int) {
	printf("%s\n", __PRETTY_FUNCTION__);

	data_.font_color_ = gru::Color::green<float>();

	return 1;
}



