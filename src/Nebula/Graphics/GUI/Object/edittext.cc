
#include <Nebula/Graphics/window/window.hpp>
#include <Nebula/Graphics/gui/layout.hpp>
#include <Nebula/Graphics/gui/object/edittext.hpp>

Neb::gui::object::edittext::edittext()
{

}
void	Neb::gui::object::edittext::draw()
{

}

void	Neb::gui::object::edittext::connect()
{
	//std::shared_ptr<Neb::window> w = get_window();
/*
	conns_.key_fun_ = w->sig_.key_fun_.connect(
			std::bind(&Neb::gui::object::object::key_fun,
				this,
				std::placeholders::_1,
				std::placeholders::_2,
				std::placeholders::_3,
				std::placeholders::_4
				));
*/
}
int	Neb::gui::object::edittext::mouse_button_fun(int button, int action, int mods)
{
	return 0;
}
int	Neb::gui::object::edittext::key_fun(int key, int scancode, int action, int mods) {
	char k = 'a' - GLFW_KEY_A + key;

	if(action == GLFW_PRESS) {
		switch(key) {
			case GLFW_KEY_BACKSPACE:
				if(!data_.label_.empty()) {
					data_.label_.pop_back();
				}
				return 1;
			case GLFW_KEY_A:
			case GLFW_KEY_Z:
				data_.label_.push_back(k);
				return 1;
			case GLFW_KEY_ENTER:
				return enter();
			default:
				return 0;
		}
	}
	
	return 0;
}
int	Neb::gui::object::edittext::enter()
{
	return 1;	
}

