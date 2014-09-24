#include <neb/gfx/util/log.hpp>
#include <neb/gfx/window/Base.hh>
#include <neb/gfx/app/glfw.hpp>

neb::gfx::app::glfw * const				neb::gfx::app::glfw::global()
{
	auto app = dynamic_cast<neb::gfx::app::glfw*>(g_app_.get());
	assert(app);
	return app;
}
void							neb::gfx::app::glfw::static_error_fun(int error, char const * description) {
	printf("%s\n", description);
	abort();
	//throw neb::gfx::exception();
}
void							neb::gfx::app::glfw::static_window_pos_fun(GLFWwindow* window, int x, int y){
	//GLUTPP_DEBUG_0_FUNCTION;

	auto w = neb::gfx::app::glfw::global()->get_window(window).lock();

	w->callback_window_pos_fun(window,x,y);
}
void							neb::gfx::app::glfw::static_window_size_fun(GLFWwindow* window, int width, int h){
	//GLUTPP_DEBUG_0_FUNCTION;

	auto w = neb::gfx::app::glfw::global()->get_window(window).lock();

	w->callback_window_size_fun(window, width, h);
}
void							neb::gfx::app::glfw::static_window_close_fun(GLFWwindow* window){
	//GLUTPP_DEBUG_0_FUNCTION;

	auto w = neb::gfx::app::glfw::global()->get_window(window).lock();

	w->callback_window_close_fun(window);
}
void							neb::gfx::app::glfw::static_window_refresh_fun(GLFWwindow* window) {
	//GLUTPP_DEBUG_0_FUNCTION;

	auto w = neb::gfx::app::glfw::global()->get_window(window).lock();

	w->callback_window_refresh_fun(window);
}
void							neb::gfx::app::glfw::static_mouse_button_fun(GLFWwindow* window, int button, int action, int mods){
	//GLUTPP_DEBUG_0_FUNCTION;

	auto w = neb::gfx::app::glfw::global()->get_window(window).lock();

	w->callback_mouse_button_fun(window, button, action, mods);
}
void							neb::gfx::app::glfw::static_key_fun(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	//GLUTPP_DEBUG_0_FUNCTION;

	auto w = neb::gfx::app::glfw::global()->get_window(window).lock();

	w->callback_key_fun(window, key, scancode, action, mods);
}
void							neb::gfx::app::glfw::staticCharFun(GLFWwindow* window, unsigned int codepoint)
{
	auto w = neb::gfx::app::glfw::global()->get_window(window).lock();
	w->callbackCharFun(window, codepoint);
}

void					neb::gfx::app::glfw::init()
{

	glfwSetErrorCallback(static_error_fun);
	try
	{
		glfwInit();
		flag_.set(neb::core::app::util::flag::INIT_GLFW);
	}
	catch(std::exception& e)
	{
	}
}
void				neb::gfx::app::glfw::init_glew()
{
	if(!flag_.any(neb::core::app::util::flag::INIT_GLEW))
	{
		GLenum err = glewInit();
		if (err != GLEW_OK)
		{
			printf("GLEW: %s\n", glewGetErrorString(err));
			exit(EXIT_FAILURE);
		}

		flag_.set(neb::core::app::util::flag::INIT_GLEW);
	}
}
void				neb::gfx::app::glfw::release()
{
}
void				neb::gfx::app::glfw::step(gal::etc::timestep const & ts)
{

	neb::gfx::window::util::parent::step(ts);

}
void				neb::gfx::app::glfw::render()
{
	LOG(lg, neb::gfx::sl, debug) << __PRETTY_FUNCTION__;

	neb::gfx::window::util::parent::render();

}
std::weak_ptr<neb::gfx::window::base>			neb::gfx::app::glfw::get_window(GLFWwindow* window) {
	auto it = windows_glfw_.find(window);
	assert(it != windows_glfw_.cend());
	assert(it->second);
	return it->second;
}


