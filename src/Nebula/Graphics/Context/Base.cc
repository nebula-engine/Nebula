//#include <assert.h>

#include <Nebula/Scene/Base.hh>
#include <Nebula/Graphics/Context/Base.hh>
#include <Nebula/Graphics/GUI/Layout/Base.hh>
#include <Nebula/Graphics/Camera/View/Free.hh>
#include <Nebula/Graphics/Camera/Projection/Perspective.hh>



Neb::Graphics::Context::Base::Base(Neb::Graphics::Context::Util::Parent_s parent): parent_(parent) {
	printf("%s\n",__PRETTY_FUNCTION__);
}
Neb::Graphics::Context::Base&		Neb::Graphics::Context::Base::operator=(Neb::Graphics::Context::Base const & r){
	printf("%s\n",__PRETTY_FUNCTION__);
	return *this;
}
void Neb::Graphics::Context::Base::init() {
	printf("%s\n",__PRETTY_FUNCTION__);
	
	// camera
	view_.reset(new Neb::Graphics::Camera::View::Free);
	proj_.reset(new Neb::Graphics::Camera::Projection::Perspective(isContextBase()));
	//camera_->init(shared_from_this());
}
void Neb::Graphics::Context::Base::resize(int w, int h) {
	//camera_->w_ = w;
	//camera_->h_ = h;
}
void Neb::Graphics::Context::Base::render(double time, Neb::Graphics::Window::Base_s window) {

	GLUTPP_DEBUG_1_FUNCTION;

	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	auto scene = scene_.lock();
	auto layout = layout_.lock();

	if(scene) {
		scene->render(time, view_, proj_, window);
	}

	if(layout) {
		//layout_->render(time);
	}
}		





