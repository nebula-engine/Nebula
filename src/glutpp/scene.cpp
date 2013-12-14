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
void	glutpp::scene::shaders()
{
	printf("%s\n",__PRETTY_FUNCTION__);
	
	// remove old program
	if(program_)
	{
		delete program_;
	}
	
	std::map<unsigned int,int> shader_map;
	
	unsigned int m = 
		RAY_TRACE |
		LIGHTING | 
		SHADOW | 
		REFLECT |
		REFLECT_PLANAR |
		REFLECT_CURVED |
		TEX_IMAGE |
		TEX_NORMAL_MAP;

	// populate map based on platform capability
	shader_map[ LIGHTING ] = 0;
	shader_map[ LIGHTING | SHADOW ] = 1;
	
	if(all(SHADER))
	{
		printf("shaders enabled\n");
		
		unsigned int f = mask(m);

		auto it = shader_map.find(f);

		if(it == shader_map.end()) fatal_error("shader configuration %i not implemented",f);

		int s = it->second;

		program_ = new program;
		program_->init();

		shaders_.clear();
		switch(s)
		{
			case 0:
				shaders_.emplace_back();
				shaders_.emplace_back();
				
				shaders_.at(0).load(GLUTPP_SHADER_DIR"/prog_0/vs.glsl", GL_VERTEX_SHADER);
				shaders_.at(1).load(GLUTPP_SHADER_DIR"/prog_0/fs.glsl", GL_FRAGMENT_SHADER);
				
				shader_count_ = 2;
				break;
			case 1:
				shaders_.emplace_back();
				shaders_.emplace_back();
				
				shaders_.at(0).load(GLUTPP_SHADER_DIR"/prog_1/vs.glsl", GL_VERTEX_SHADER);
				shaders_.at(1).load(GLUTPP_SHADER_DIR"/prog_1/fs.glsl", GL_FRAGMENT_SHADER);
				
				shader_count_ = 2;
				break;
			default:
				fatal_error("shader configuration %i not implemented",f);
				break;
		}
		
		program_->add_shaders(shaders_,shader_count_);
		program_->compile();
		program_->use();
	}
	else
	{
		printf("shaders not enabled\n");
	}
}
void	glutpp::scene::render(double time)
{
	printf("%s\n",__PRETTY_FUNCTION__);

	// uniforms
	uniforms_.light_count_.load_1i(light_count_);
	lights_for_each(&glutpp::light::load);
	
	if(all(SHADOW)) lights_for_each(&glutpp::light::RenderLightPOV);
	
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	
	camera_.load();
	
	//if(all(SHADOW) && !all(SHADER)) display_dim();
	
	display_bright();
}
void	glutpp::scene::uniforms()
{
	printf("%s\n",__PRETTY_FUNCTION__);

	uniforms_.light_count_.init(this,"light_count");
	uniforms_.model_.init(this,"model");
	uniforms_.view_.init(this,"view");
	uniforms_.proj_.init(this,"proj");
}
void	glutpp::scene::display_bright()
{
	//printf("%s\n",__PRETTY_FUNCTION__);
	
	lights_for_each(&glutpp::light::load);
	
	if(all(REFLECT | REFLECT_PLANAR)) objects_for_each(&glutpp::object::render_reflection);
	
	draw();
	
	check_error();
	
	if(all(SHADOW)) lights_for_each(&glutpp::light::RenderShadowPost);
}
void	glutpp::scene::draw()
{
	for( auto it = objects_.begin(); it != objects_.end(); ++it )
	{
		(*it)->draw();
	}
}
void	glutpp::scene::resize(int w, int h)
{
	camera_.w_ = w;
	camera_.h_ = h;
}






