
#include <neb/gfx/window/Base.hh>
#include <neb/gfx/GUI/Layout/Base.hh>
#include <neb/gfx/GUI/Object/edittext.hh>

neb::gfx::gui::object::edittext::edittext() {

}
void	neb::gfx::gui::object::edittext::draw() {

}

void	neb::gfx::gui::object::edittext::connect() {
	//std::shared_ptr<neb::window> w = get_window();
/*
	conns_.key_fun_ = w->sig_.key_fun_.connect(
			std::bind(&neb::gfx::gui::object::object::key_fun,
				this,
				std::placeholders::_1,
				std::placeholders::_2,
				std::placeholders::_3,
				std::placeholders::_4
				));
*/
}
int	neb::gfx::gui::object::edittext::mouse_button_fun(int button, int action, int mods) {
	return 0;
}
int	neb::gfx::gui::object::edittext::key_fun(int key, int scancode, int action, int mods) {
	char k = 'a' - GLFW_KEY_A + key;

	if(action == GLFW_PRESS) {
		switch(key) {
			case GLFW_KEY_BACKSPACE:
				if(!label_.empty()) {
					label_.pop_back();
				}
				return 1;
			case GLFW_KEY_A:
			case GLFW_KEY_Z:
				label_.push_back(k);
				return 1;
			case GLFW_KEY_ENTER:
				return enter();
			default:
				return 0;
		}
	}
	
	return 0;
}
int	neb::gfx::gui::object::edittext::enter()
{
	return 1;	
}

