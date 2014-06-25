#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <gal/log/log.hpp>

#include <neb/debug.hh>
#include <neb/free.hh>
#include <neb/app/Base.hh>
#include <neb/gfx/GUI/Object/terminal.hh>

void		neb::gfx::gui::object::terminal::init() {
	if(DEBUG_NEB) BOOST_LOG_CHANNEL_SEV(lg, "neb gfx gui", debug) << __PRETTY_FUNCTION__;

	neb::gfx::gui::object::base::init();

	auto app = neb::app::base::global();

	cs_ = app->command_set_;

	assert(cs_);
}
void		neb::gfx::gui::object::terminal::draw(sp::shared_ptr<neb::glsl::program> p) {
	if(DEBUG_NEB) BOOST_LOG_CHANNEL_SEV(lg, "neb gfx gui", debug) << __PRETTY_FUNCTION__;

	if(!flag_.any(neb::gfx::gui::object::util::flag::ENABLED)) return;

	float sx = 1.0/ 600.0;
	float sy = 1.0/ 600.0;

	//draw_quad(x_, y_, w_, h_, bg_color_);

	float y = y_ + 0.5;
	float line_height = 0.1;

	for(auto l : lines_) {
		draw_text(p, x_, y, sx, sy, font_color_, l.c_str());
		y -= line_height;
	}

	::std::string line = "$ " + line_;

	draw_text(p, x_, y, sx, sy, font_color_, line.c_str());

}
int			neb::gfx::gui::object::terminal::key_fun(
		sp::shared_ptr<neb::gfx::window::base> const & window,
		int key,
		int scancode,
		int action,
		int mods)
{
	if(DEBUG_NEB) BOOST_LOG_CHANNEL_SEV(lg, "neb gfx gui", debug) << __PRETTY_FUNCTION__;


	char k =	'a' - GLFW_KEY_A + key;
	char k_num =	'0' - GLFW_KEY_0 + key;

	if(!flag_.any(neb::gfx::gui::object::util::flag::ENABLED) && !(key == GLFW_KEY_ESCAPE)) {
		return 0;
	}

	if(action == GLFW_PRESS) {
		switch(key) {
			case GLFW_KEY_ESCAPE:
				flag_.toggle(neb::gfx::gui::object::util::flag::ENABLED);
				break;
			case GLFW_KEY_BACKSPACE:
				if(!line_.empty()) {
					line_.pop_back();
				}
				break;
			case GLFW_KEY_SPACE:
				push(' ');
				break;
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
				push(k);
				break;
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
				push(k_num);
				break;
			case GLFW_KEY_ENTER:
				enter();
				break;
		}
	}

	// block everything
	return 1;
}




