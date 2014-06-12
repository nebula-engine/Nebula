#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <Nebula/free.hh>
#include <Nebula/App/Base.hh>
#include <Nebula/Graphics/GUI/Object/terminal.hh>

void		neb::gfx::GUI::Object::terminal::draw(sp::shared_ptr<neb::glsl::program> p) {
	
	printf("%s\n",__PRETTY_FUNCTION__);
	
	float sx = 1.0/ 600.0;
	float sy = 1.0/ 600.0;
	
	//draw_quad(x_, y_, w_, h_, bg_color_);
	
	float y = y_ + 0.5;
	float line_height = 0.1;
	
	for(auto l : lines_) {
		l = "$ " + l;
		draw_text(p, x_, y, sx, sy, font_color_, l.c_str());
		y -= line_height;
	}
	
	::std::string line = "$ " + line_;

	draw_text(p, x_, y, sx, sy, font_color_, line.c_str());
	
}
int			neb::gfx::GUI::Object::terminal::key_fun(
		sp::shared_ptr<neb::gfx::Window::Base> const & window,
		int key,
		int scancode,
		int action,
		int mods)
{
	printf("%s\n",__PRETTY_FUNCTION__);
	
	char k =	'a' - GLFW_KEY_A + key;
	char k_num =	'0' - GLFW_KEY_0 + key;
	
	if(action == GLFW_PRESS) {
		switch(key) {
			case GLFW_KEY_BACKSPACE:
				line_.pop_back();
				return 1;
			case GLFW_KEY_A:
			case GLFW_KEY_B:
			case GLFW_KEY_C:
			case GLFW_KEY_D:
			case GLFW_KEY_E:
			case GLFW_KEY_F:
			case GLFW_KEY_G:
			case GLFW_KEY_H:
			case GLFW_KEY_I:
			case GLFW_KEY_J:
			case GLFW_KEY_K:
			case GLFW_KEY_L:
			case GLFW_KEY_M:
			case GLFW_KEY_N:
			case GLFW_KEY_O:
			case GLFW_KEY_P:
			case GLFW_KEY_Q:
			case GLFW_KEY_R:
			case GLFW_KEY_S:
			case GLFW_KEY_T:
			case GLFW_KEY_U:
			case GLFW_KEY_V:
			case GLFW_KEY_W:
			case GLFW_KEY_X:
			case GLFW_KEY_Y:
			case GLFW_KEY_Z:
				line_.push_back(k);
				return 1;
			case GLFW_KEY_0:
			case GLFW_KEY_1:
			case GLFW_KEY_2:
			case GLFW_KEY_3:
			case GLFW_KEY_4:
			case GLFW_KEY_5:
			case GLFW_KEY_6:
			case GLFW_KEY_7:
			case GLFW_KEY_8:
			case GLFW_KEY_9:
				line_.push_back(k_num);
				return 1;
			case GLFW_KEY_ENTER:
				return enter();
			default:
				return 0;
		}
	}

	return 0;
}
int neb::gfx::GUI::Object::terminal::enter() {

	auto self = sp::dynamic_pointer_cast<neb::gfx::GUI::Object::terminal>(shared_from_this());

	neb::App::Base::global()->command(self, line_);

	//lines_.push_back(line_);
	line_.clear();

	if(lines_.size() > max_line_count)
	{
		lines_.pop_front();
	}

	return 1;
}



