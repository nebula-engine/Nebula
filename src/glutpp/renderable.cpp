//#include <assert.h>

#include <glutpp/scene.h>
#include <glutpp/renderable.h>
#include <glutpp/gui/layout.h>

glutpp::renderable::renderable()
{
	printf("%s\n",__PRETTY_FUNCTION__);
}
glutpp::renderable&	glutpp::renderable::operator=(glutpp::renderable const & r)
{
	printf("%s\n",__PRETTY_FUNCTION__);
}
void	glutpp::renderable::init(std::shared_ptr<window> window)
{
	printf("%s\n",__PRETTY_FUNCTION__);

	assert(window);
	
	window_ = window;

	// programs
	programs_.text_.reset(new program);
	programs_.text_->init();

	std::vector<glutpp::shader> shaders;

	shaders.emplace_back();
	shaders.emplace_back();

	shaders.at(0).load(GLUTPP_SHADER_DIR"/text/vs.glsl", GL_VERTEX_SHADER);
	shaders.at(1).load(GLUTPP_SHADER_DIR"/text/fs.glsl", GL_FRAGMENT_SHADER);

	programs_.text_->add_shaders(shaders);
	programs_.text_->compile();


	// scene
	scene_.reset(new glutpp::scene);
	scene_->init(shared_from_this());

	// layout
	layout_.reset(new glutpp::gui::layout);
	layout_->init(shared_from_this());
}
void	glutpp::renderable::resize(int w, int h)
{
	scene_->resize(w,h);
}
void	glutpp::renderable::render(double time)
{
	printf("%s\n",__PRETTY_FUNCTION__);

	if(scene_) scene_->render(time);
	
	if(layout_)
	{
		assert(programs_.text_);
		programs_.text_->use();
		
		
		layout_->render(time);
	}
}
