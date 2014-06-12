#include <string.h>
#include <algorithm>

#include <Nebula/Graphics/GUI/Object/Base.hh>

neb::gfx::GUI::Object::Base::Base():
	x_(0.0),
	y_(0.0),
	w_(0.3),
	h_(0.3),
	font_color_(neb::Color::magenta<float>()),
	bg_color_(0,0,0,0)
{}
void		neb::gfx::GUI::Object::Base::init() {
	neb::std::shared::init();
}
int		neb::gfx::GUI::Object::Base::mouse_button_fun(sp::shared_ptr<neb::gfx::Window::Base> const & window, int,int,int) {
	printf("%s\n", __PRETTY_FUNCTION__);

	font_color_ = neb::Color::green<float>();

	return 1;
}



