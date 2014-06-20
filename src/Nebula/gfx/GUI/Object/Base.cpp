#include <string.h>
#include <algorithm>

#include <Nebula/gfx/GUI/Object/Base.hh>

neb::gfx::gui::object::base::base():
	x_(0.0),
	y_(0.0),
	w_(0.3),
	h_(0.3),
	font_color_(neb::Color::magenta<float>()),
	bg_color_(0,0,0,0)
{}
void		neb::gfx::gui::object::base::init() {
	neb::std::shared::init();
}
int		neb::gfx::gui::object::base::mouse_button_fun(sp::shared_ptr<neb::gfx::window::base> const & window, int,int,int) {
	printf("%s\n", __PRETTY_FUNCTION__);

	font_color_ = neb::Color::green<float>();

	return 1;
}



