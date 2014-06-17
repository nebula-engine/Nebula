#include <Nebula/App/Base.hh>

void					neb::app::__gfx::static_error_fun(int error, char const * description) {
	printf("%s\n", description);
	exit(0);
}
void					neb::app::__gfx::static_window_pos_fun(GLFWwindow* window, int x, int y){
	//GLUTPP_DEBUG_0_FUNCTION;

	auto w = neb::app::base::global()->get_window(window);

	w->callback_window_pos_fun(window,x,y);
}
void					neb::app::__gfx::static_window_size_fun(GLFWwindow* window, int width, int h){
	//GLUTPP_DEBUG_0_FUNCTION;

	auto w = neb::app::base::global()->get_window(window);

	w->callback_window_size_fun(window, width, h);
}
void					neb::app::__gfx::static_window_close_fun(GLFWwindow* window){
	//GLUTPP_DEBUG_0_FUNCTION;

	auto w = neb::app::base::global()->get_window(window);

	w->callback_window_close_fun(window);
}
void					neb::app::__gfx::static_window_refresh_fun(GLFWwindow* window) {
	//GLUTPP_DEBUG_0_FUNCTION;

	auto w = neb::app::base::global()->get_window(window);

	w->callback_window_refresh_fun(window);
}
void					neb::app::__gfx::static_mouse_button_fun(GLFWwindow* window, int button, int action, int mods){
	//GLUTPP_DEBUG_0_FUNCTION;

	auto w = neb::app::base::global()->get_window(window);

	w->callback_mouse_button_fun(window, button, action, mods);
}
void neb::app::__gfx::static_key_fun(GLFWwindow* window, int key, int scancode, int action, int mods){
	//GLUTPP_DEBUG_0_FUNCTION;

	auto w = neb::app::base::global()->get_window(window);

	w->callback_key_fun(window, key, scancode, action, mods);
}



