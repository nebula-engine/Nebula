#include <string.h>
#include <algorithm>

#include <Nebula/Graphics/gui/object/object.hpp>

Neb::gui::object::Data::Data():
	x_(0.0),
	y_(0.0),
	w_(0.3),
	h_(0.3),
	font_color_(Neb::Color::magenta<float>()),
	bg_color_(0,0,0,0)
{}



Neb::gui::object::object::object()
{
}
void Neb::gui::object::object::i(int ni) {
	i_ = ni;
}
Neb::window::window_s get_window() {
	printf("%s\n", __PRETTY_FUNCTION__);
	printf("not yet supported");
	abort();
}
int	Neb::gui::object::object::mouse_button_fun(int,int,int) {
	printf("%s\n", __PRETTY_FUNCTION__);

	data_.font_color_ = Neb::Color::green<float>();

	return 1;
}



