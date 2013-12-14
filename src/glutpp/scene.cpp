#include <stdio.h>

#include <glutpp/window.h>
#include <glutpp/scene.h>
#include <glutpp/object.h>
#include <glutpp/light.h>

glutpp::scene::scene():
	light_count_(0)
{
	memset(lights_, 0, LIGHT_MAX);
}
void	glutpp::scene::init(std::shared_ptr<renderable> renderable)
{
	renderable_ = renderable;
	
	camera_.init(shared_from_this());
}
void	glutpp::scene::add_object(object* o)
{
	printf("%s\n",__PRETTY_FUNCTION__);
	
	if(o == NULL)
	{
		printf("object is NULL\n");
		return;
	}
	
	objects_.push_back(o);
	
	o->init(this);
	o->init_buffer();
}
void	glutpp::scene::add_light(light* l)
{
	printf("%s\n",__PRETTY_FUNCTION__);
	
	if(light_count_ == LIGHT_MAX)
	{
		printf("max light\n");
		return;
	}
	
	if(l == NULL)
	{
		printf("light is NULL\n");
		return;
	}
	
	lights_[light_count_] = l;
	
	l->init(shared_from_this(), light_count_);
	
	light_count_++;
	
	printf("%s exit\n",__PRETTY_FUNCTION__);
}
void	glutpp::scene::objects_for_each(std::function<void(glutpp::object*)> func)
{	
	//printf("%s\n",__PRETTY_FUNCTION__);

	for(int i = 0; i < objects_.size(); ++i)
	{
		if(lights_[i] == NULL)
		{
			printf("light is NULL\n");
			exit(0);
		}

		func(objects_.at(i));
	}
}
void	glutpp::scene::lights_for_each(std::function<void(glutpp::light*)> func)
{	
	//printf("%s\n",__PRETTY_FUNCTION__);

	for(int i = 0; i < light_count_; ++i)
	{
		if(lights_[i] == NULL)
		{
			printf("light is NULL\n");
			exit(0);
		}
		
		func(lights_[i]);
	}
}
void	glutpp::scene::render(double time)
{
	printf("%s\n",__PRETTY_FUNCTION__);

	// uniforms
	uniforms_.light_count_.load_1i(light_count_);
	lights_for_each(&glutpp::light::load);
	
	if(all(glutpp::window::SHADOW)) lights_for_each(&glutpp::light::RenderLightPOV);
	
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	camera_.load();

	//if(all(SHADOW) && !all(SHADER)) display_dim();

	display_bright();
	
	if(all(ORTHO)) draw_ortho();
	
	glFinish();
	glfwSwapBuffers(window_);
	//glfwPostRedisplay();
}
void	glutpp::scene::draw()
{
	for( auto it = objects_.begin(); it != objects_.end(); ++it )
	{
		(*it)->draw();
	}
}
void	glutpp::scene::resize()
{
	camera_.w_ = w_;
	camera_.h_ = h_;
}






