//#include <assert.h>

#include <glutpp/scene.h>
#include <glutpp/renderable.h>
#include <glutpp/gui/layout.h>

glutpp::renderable::renderable(){
	printf("%s\n",__PRETTY_FUNCTION__);
}
glutpp::renderable&	glutpp::renderable::operator=(glutpp::renderable const & r){
	printf("%s\n",__PRETTY_FUNCTION__);
}
void	glutpp::renderable::init(std::shared_ptr<window> window) {
	printf("%s\n",__PRETTY_FUNCTION__);

	assert(window);
	
	window_ = window;
	
	// camera
	camera_.reset(new glutpp::camera);
	camera_->init(shared_from_this());
}
void	glutpp::renderable::resize(int w, int h){
	camera_->w_ = w;
	camera_->h_ = h;
}
void	glutpp::renderable::render(double time, std::shared_ptr<glutpp::window> window) {

	printf("%s\n",__PRETTY_FUNCTION__);

	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	if(scene_)
	{
		scene_->render(time, camera_, window);
	}
	
	if(layout_)
	{
		layout_->render_shader(time);
	}
}







