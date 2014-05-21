#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <Nebula/free.hh>
#include <Nebula/App/Base.hh>
#include <Nebula/Graphics/GUI/Object/terminal.hh>

void	Neb::Graphics::GUI::Object::terminal::draw() {
	//printf("%s\n",__PRETTY_FUNCTION__);
	
	float sx = 1.0/1200.0;
	float sy = 1.0/1200.0;
	
	//draw_quad(x_, y_, w_, h_, bg_color_);
	
	float y = y_ + 1.0;
	float line_height = 0.1;
	
	for(auto it = lines_.begin(); it != lines_.end(); ++it) {
		draw_text(x_, y, sx, sy, font_color_, it->c_str());
		y -= line_height;
	}
	
	draw_text(x_, y_, sx, sy, font_color_, line_.c_str());
	
}
int	Neb::Graphics::GUI::Object::terminal::key_fun(int key, int scancode, int action, int mods) {
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
int Neb::Graphics::GUI::Object::terminal::enter() {
	
	Neb::App::Base::globalBase()->command(line_);
	
	lines_.push_back(line_);
	line_.clear();
	
	if(lines_.size() > max_line_count)
	{
		lines_.pop_front();
	}
	
	return 1;
}



