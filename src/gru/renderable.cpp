//#include <assert.h>

#include <gru/scene/scene.hpp>
#include <gru/renderable.hpp>
#include <gru/gui/layout.hpp>
#include <gru/Camera/View/Free.hpp>



glutpp::renderable::renderable(glutpp::window::window_s window): window_(window)
{
	printf("%s\n",__PRETTY_FUNCTION__);
}
glutpp::renderable& glutpp::renderable::operator=(renderable const & r){
	printf("%s\n",__PRETTY_FUNCTION__);
}
unsigned int glutpp::renderable::f() {
	return flag_;
}
void glutpp::renderable::f(unsigned int flag) {
	flag_ = flag;
}
void glutpp::renderable::init(glutpp::window::window_s window) {
	printf("%s\n",__PRETTY_FUNCTION__);

	assert(window);

	window_ = window;

	// camera
	view_.reset(new glutpp::Camera::View::Free);
	//camera_->init(shared_from_this());
}
glutpp::window::window_s glutpp::renderable::get_window() {
	auto window = window_.lock();

	assert(window);

	return window;
}
void glutpp::renderable::resize(int w, int h) {
	//camera_->w_ = w;
	//camera_->h_ = h;
}
void glutpp::renderable::render(double time, glutpp::window::window_s window) {

	GLUTPP_DEBUG_1_FUNCTION;

	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	
	if(scene_) {
		scene_->render(time, view_, window);
	}

	if(layout_)
	{
		layout_->render(time);
	}
}		





