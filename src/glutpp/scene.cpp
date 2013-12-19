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
void	glutpp::scene::init(std::shared_ptr<renderable> renderable){
	assert(renderable);

	renderable_ = renderable;
}
void	glutpp::scene::add_actor(std::shared_ptr<actor> actor) {
	printf("%s\n",__PRETTY_FUNCTION__);
	
	assert(actor);
	
	actors_.push(actor);
	
	actor->init(shared_from_this());
}
int	glutpp::scene::prepare() {
	
	if(glutpp::__master.all(glutpp::master::option::SHADERS))
	{
		auto p = glutpp::__master.get_program(glutpp::program_name::e::LIGHT);
		
		actors_.foreach<glutpp::actor>(std::bind(&glutpp::actor::init_buffer, std::placeholders::_1, p));
	}
	
	return 0;
}
void	glutpp::scene::add_light(std::shared_ptr<light> l) {
	printf("%s\n",__PRETTY_FUNCTION__);
	
	assert(l);
	
	lights_.push(l);
	
	l->init(shared_from_this(), lights_.next_ - 1);
}
void	glutpp::scene::render_shader(double time) {
	printf("%s\n",__PRETTY_FUNCTION__);
	
	assert(!renderable_.expired());
	auto cam = renderable_.lock()->camera_;
	assert(cam);
	
	auto p = glutpp::__master.use_program(glutpp::program_name::e::LIGHT);
	
	p->get_uniform(glutpp::uniform_name::LIGHT_COUNT)->load(lights_.next_);
	
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	cam->load_shader();
	
	lights_.foreach<glutpp::light>(&glutpp::light::load_shader);

	draw_shader();
}
void	glutpp::scene::render_no_shader(double time) {
	printf("%s\n",__PRETTY_FUNCTION__);

	auto cam = renderable_.lock()->camera_;

	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	cam->load_no_shader();

	lights_.foreach<glutpp::light>(&glutpp::light::load_no_shader);

	draw_no_shader();
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
int	glutpp::scene::draw_no_shader() {

	printf("%s\n",__PRETTY_FUNCTION__);
	
	actors_.foreach<glutpp::actor>(&glutpp::actor::draw_no_shader);
}
int	glutpp::scene::draw_shader() {
	
	printf("%s\n",__PRETTY_FUNCTION__);
	
	actors_.foreach<glutpp::actor>(&glutpp::actor::draw_shader);
}
void	glutpp::scene::resize(int w, int h) {
}





