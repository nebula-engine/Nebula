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
void	glutpp::renderable::init(std::shared_ptr<window> window){
	printf("%s\n",__PRETTY_FUNCTION__);

	assert(window);
	
	window_ = window;
	
	// camera
	camera_.reset(new glutpp::camera);
	camera_->init(shared_from_this());

/*	// scene
	scene_.reset(new glutpp::scene);
	scene_->init(shared_from_this());

	scene_->set(glutpp::scene::SHADER);
        scene_->set(glutpp::scene::LIGHTING);
*/	
	//scene_->shaders();
	//scene_->uniforms();

	// layout
/*	layout_.reset(new glutpp::gui::layout);
	layout_->init(shared_from_this());
	layout_->connect();*/
}
void	glutpp::renderable::resize(int w, int h){
	camera_->w_ = w;
	camera_->h_ = h;
	
	scene_->resize(w,h);
}
void	glutpp::renderable::render(double time){
	printf("%s\n",__PRETTY_FUNCTION__);

	if(scene_)
	{
		scene_->render_shader_light(time);
	}
	
	if(layout_)
	{
		layout_->render_shader(time);
	}
}
