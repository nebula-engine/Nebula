#include <stdio.h>


#include <glutpp/window.h>
#include <glutpp/renderable.h>
#include <glutpp/scene.h>
#include <glutpp/actor.h>
#include <glutpp/light.h>

#include <glutpp/glsl/program.h>

glutpp::scene::scene() {
}
glutpp::scene::~scene() {
	printf("%s\n",__PRETTY_FUNCTION__);
}
void	glutpp::scene::init(std::shared_ptr<renderable> renderable) {

	assert(renderable);

	//renderable_ = renderable;
}
int	glutpp::scene::remove_actor(int i) {

	printf("%s\n",__PRETTY_FUNCTION__);

	auto it = actors_.map_.find(i);
	
	it->second->release();
	
	actors_.map_.erase(it);
}
int	glutpp::scene::remove_light(int i) {

	printf("%s\n",__PRETTY_FUNCTION__);

	auto it = lights_.map_.find(i);
	
	it->second->release();
	
	lights_.map_.erase(it);
}
void	glutpp::scene::add_actor(std::shared_ptr<actor> actor) {

	printf("%s\n",__PRETTY_FUNCTION__);
	
	assert(actor);
	
	actors_.push(actor);
	
	actor->scene_ = shared_from_this();
}
int	glutpp::scene::prepare() {

	printf("%s\n",__PRETTY_FUNCTION__);

	//auto p = glutpp::__master.get_program(glutpp::program_name::e::LIGHT);

	//actors_.foreach<glutpp::actor>(std::bind(&glutpp::actor::init_buffer, std::placeholders::_1, p));

	return 0;
}
void	glutpp::scene::add_light(std::shared_ptr<light> l) {
	printf("%s\n",__PRETTY_FUNCTION__);

	assert(l);

	lights_.push(l);

	l->init(shared_from_this());
}
void	glutpp::scene::render(double time, std::shared_ptr<glutpp::camera> camera, std::shared_ptr<glutpp::window> window) {
	
	printf("%s\n",__PRETTY_FUNCTION__);

	assert(camera);

	//assert(!renderable_.expired());
	//auto cam = renderable_.lock()->camera_;
	//assert(cam);
	
	auto p = glutpp::__master.use_program(glutpp::program_name::e::LIGHT);
	
	int light_count = lights_.map_.size();
	p->get_uniform(glutpp::uniform_name::LIGHT_COUNT)->load(light_count);
	
	
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);

	camera->load();

	int i = 0;
	for(auto it = lights_.map_.begin(); it != lights_.map_.end(); ++it)
	{
		it->second->load_shader(i++);
	}

	draw(window);
}
/*void	glutpp::scene::render(double time)
  {
  printf("%s\n",__PRETTY_FUNCTION__);

  std::shared_ptr<glutpp::glsl::program> p = glutpp::__master.get_program(glutpp::program_name::e::LIGHT);
  p->use();

// uniforms
p->get_uniform(glutpp::uniform_name::e::LIGHT_COUNT)->load(light_count_);
lights_for_each(&glutpp::light::load);

if(all(SHADOW)) lights_for_each(&glutpp::light::RenderLightPOV);

glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

camera_.load();

//if(all(SHADOW) && !all(SHADER)) display_dim();

lights_for_each(&glutpp::light::load);

if(all(REFLECT | REFLECT_PLANAR)) actors_for_each(&glutpp::object::render_reflection);

draw();

//check_error();

if(all(SHADOW)) lights_for_each(&glutpp::light::RenderShadowPost);


//display_bright();
}*/
/*void	glutpp::scene::uniforms()
  {
  printf("%s\n",__PRETTY_FUNCTION__);

  uniforms_.light_count_.init(shared_from_this(),"light_count");
  uniforms_.model_.init(shared_from_this(),"model");
  uniforms_.view_.init(shared_from_this(),"view");
  uniforms_.proj_.init(shared_from_this(),"proj");
  }*/
/*void	glutpp::scene::display_bright()
  {
//printf("%s\n",__PRETTY_FUNCTION__);

lights_for_each(&glutpp::light::load);

if(all(REFLECT | REFLECT_PLANAR)) actors_for_each(&glutpp::object::render_reflection);

draw();

check_error();

if(all(SHADOW)) lights_for_each(&glutpp::light::RenderShadowPost);
}*/
int	glutpp::scene::draw(std::shared_ptr<glutpp::window> window) {

	printf("%s\n",__PRETTY_FUNCTION__);

	for(auto it = actors_.map_.begin(); it != actors_.map_.end(); ++it)
	{
		it->second->draw(window);
	}
}
void	glutpp::scene::resize(int w, int h) {
}





