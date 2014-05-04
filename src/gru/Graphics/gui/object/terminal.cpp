
#include <gru/free.hpp>
#include <gru/Graphics/gui/object/terminal.hpp>

void	glutpp::gui::object::terminal::draw()
{
	//printf("%s\n",__PRETTY_FUNCTION__);
	
	float sx = 1.0/1200.0;
	float sy = 1.0/1200.0;
	
	//draw_quad(x_, y_, w_, h_, bg_color_);
	
	float y = data_.y_ + 1;
	float line_height = 0.1;
	
	for(auto it = lines_.begin(); it != lines_.end(); ++it)
	{
		draw_text(data_.x_, y, sx, sy, data_.font_color_, it->c_str());
		y -= line_height;
	}
	
	draw_text(data_.x_, data_.y_, sx, sy, data_.font_color_, line_.c_str());
	
}
int	glutpp::gui::object::terminal::key_fun(int key, int scancode, int action, int mods)
{
	char k = 'a' - GLFW_KEY_A + key;

	if(action == GLFW_PRESS)
	{
		switch(key)
		{
			case GLFW_KEY_BACKSPACE:
				line_.pop_back();
				return 1;
			case GLFW_KEY_A:
			case GLFW_KEY_Z:
				line_.push_back(k);
				return 1;
			case GLFW_KEY_ENTER:
				return enter();
			default:
				return 0;
		}
	}

	return 0;
}
int glutpp::gui::object::terminal::enter() {
	
	glutpp::master::Global()->Command(line_);
	
	lines_.push_back(line_);
	line_.clear();
	
	if(lines_.size() > max_line_count)
	{
		lines_.pop_front();
	}
	
	return 1;
}



