#include <string.h>
#include <algorithm>

#include <Nebula/Graphics/GUI/Object/Base.hh>

Neb::Graphics::GUI::Object::Base::Base():
	x_(0.0),
	y_(0.0),
	w_(0.3),
	h_(0.3),
	font_color_(Neb::Color::magenta<float>()),
	bg_color_(0,0,0,0)
{}
int		Neb::Graphics::GUI::Object::Base::mouse_button_fun(int,int,int) {
	printf("%s\n", __PRETTY_FUNCTION__);

	font_color_ = Neb::Color::green<float>();

	return 1;
}



