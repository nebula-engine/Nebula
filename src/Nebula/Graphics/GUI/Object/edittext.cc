
#include <Nebula/Graphics/Window/Base.hh>
#include <Nebula/Graphics/GUI/Layout/Base.hh>
#include <Nebula/Graphics/GUI/Object/edittext.hh>

Neb::Graphics::GUI::Object::edittext::edittext() {

}
void	Neb::Graphics::GUI::Object::edittext::draw() {

}

void	Neb::Graphics::GUI::Object::edittext::connect() {
	//std::shared_ptr<Neb::window> w = get_window();
/*
	conns_.key_fun_ = w->sig_.key_fun_.connect(
			std::bind(&Neb::Graphics::GUI::Object::object::key_fun,
				this,
				std::placeholders::_1,
				std::placeholders::_2,
				std::placeholders::_3,
				std::placeholders::_4
				));
*/
}
int	Neb::Graphics::GUI::Object::edittext::mouse_button_fun(int button, int action, int mods) {
	return 0;
}
int	Neb::Graphics::GUI::Object::edittext::key_fun(int key, int scancode, int action, int mods) {
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
int	Neb::Graphics::GUI::Object::edittext::enter()
{
	return 1;	
}

