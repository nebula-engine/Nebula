
#include <gru/window/window.hpp>
#include <gru/gui/layout.hpp>
#include <gru/gui/object/edittext.hpp>

glutpp::gui::object::edittext::edittext()
{

}
void	glutpp::gui::object::edittext::draw()
{

}

void	glutpp::gui::object::edittext::connect()
{
	//std::shared_ptr<glutpp::window> w = get_window();
/*
	conns_.key_fun_ = w->sig_.key_fun_.connect(
			std::bind(&glutpp::gui::object::object::key_fun,
				this,
				std::placeholders::_1,
				std::placeholders::_2,
				std::placeholders::_3,
				std::placeholders::_4
				));
*/
}
int	glutpp::gui::object::edittext::mouse_button_fun(int button, int action, int mods)
{
	return 0;
}
int	glutpp::gui::object::edittext::key_fun(int key, int scancode, int action, int mods)
{
	char k = 'a' - GLFW_KEY_A + key;

	if(action == GLFW_PRESS)
	{
		switch(key)
		{
			case GLFW_KEY_BACKSPACE:
				if ( label_pos_ > 0 )
				{
					--label_pos_;
					memset( (void *)( label_ + label_pos_ ), '\0', 1 );
				}
				return 1;
			case GLFW_KEY_A:
			case GLFW_KEY_Z:
				if ( label_pos_ < label_length_ )
				{
					++label_pos_;
					label_[label_pos_] = k;
				}
				return 1;
			case GLFW_KEY_ENTER:
				return enter();
			default:
				return 0;
		}
	}
	
	return 0;
}
int	glutpp::gui::object::edittext::enter()
{
	return 1;	
}

