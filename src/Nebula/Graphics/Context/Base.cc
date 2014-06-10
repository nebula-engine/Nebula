//#include <assert.h>

#include <Nebula/App/Base.hh>
#include <Nebula/Scene/Base.hh>
#include <Nebula/Graphics/Context/Base.hh>
#include <Nebula/Graphics/GUI/Layout/Base.hh>
#include <Nebula/Graphics/Camera/View/Free.hh>
#include <Nebula/Graphics/Camera/Projection/Perspective.hh>


Neb::Graphics::Context::Base::Base() {
}
Neb::Graphics::Context::Base::Base(Neb::Graphics::Context::Util::Parent_s parent): parent_(parent) {
	printf("%s\n",__PRETTY_FUNCTION__);
}
Neb::Graphics::Context::Base&		Neb::Graphics::Context::Base::operator=(Neb::Graphics::Context::Base const & r){
	printf("%s\n",__PRETTY_FUNCTION__);
	return *this;
}
void		Neb::Graphics::Context::Base::init() {
	printf("%s\n",__PRETTY_FUNCTION__);
	
	// camera
	view_.reset(new Neb::Graphics::Camera::View::Free(isContextBase()));
	proj_.reset(new Neb::Graphics::Camera::Projection::Perspective(isContextBase()));
	//camera_->init(shared_from_this());
	
}
void		Neb::Graphics::Context::Base::release() {
	printf("%s\n",__PRETTY_FUNCTION__);
}
void		Neb::Graphics::Context::Base::resize(int w, int h) {
	viewport_.resize(w,h);
}
void		Neb::Graphics::Context::Base::step(Neb::Core::TimeStep const & ts) {

}
void		Neb::Graphics::Context::Base::render() {
	/**
	 * prepare rendering environment and then call the drawable
	 */

	GLUTPP_DEBUG_1_FUNCTION;
	
	auto self = sp::dynamic_pointer_cast<Neb::Graphics::Context::Base>(shared_from_this());
	auto app = Neb::App::Base::globalBase();

	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	
	assert(proj_);
	assert(view_);
	
	app->use_program(Neb::program_name::e::LIGHT);

	viewport_.load();
	
	proj_->load();
	view_->load();
	
	if(drawable_) {
		drawable_->draw(self);
	}
}		





