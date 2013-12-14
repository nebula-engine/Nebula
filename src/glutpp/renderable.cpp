#include <glutpp/renderable.h>

void	glutpp::renderable::init(this)
{
	scene_.init(this);
}
void	glutpp::renderable::render(double time)
{
	printf("%s\n",__PRETTY_FUNCTION__);

	if(scene_) scene_->render(time);
	
	if(all(ORTHO)) if(layout_) layout_->draw();
	
	glFinish();
	glfwSwapBuffers(window_);
}
