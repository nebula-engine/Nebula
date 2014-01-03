#include <stdio.h>


#include <glutpp/window.h>
#include <glutpp/renderable.h>
#include <glutpp/scene/scene.h>
#include <glutpp/actor/actor.h>
#include <glutpp/light/light.h>

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
int	glutpp::scene::prepare() {

	printf("%s\n",__PRETTY_FUNCTION__);

	//auto p = glutpp::__master.get_program(glutpp::program_name::e::LIGHT);

	//actors_.foreach<glutpp::actor>(std::bind(&glutpp::actor::init_buffer, std::placeholders::_1, p));

	return 0;
}
void	glutpp::scene::render(
		double time,
		std::shared_ptr<glutpp::camera> camera,
		std::shared_ptr<glutpp::window> window) {
	
	GLUTPP_DEBUG_1_FUNCTION;
	
	assert(camera);

	auto p = glutpp::__master.use_program(glutpp::program_name::e::LIGHT);
	
	
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);

	camera->load();

	int i = 0;
	for(auto it = actors_.map_.begin(); it != actors_.map_.end(); ++it)
	{
		it->second->load_lights(i);
	}
	
	p->get_uniform(glutpp::uniform_name::LIGHT_COUNT)->load(i);
	
	//printf("%i\n",i);
	
	draw(window);
}
int	glutpp::scene::draw(std::shared_ptr<glutpp::window> window) {

	GLUTPP_DEBUG_1_FUNCTION;

	for(auto it = actors_.map_.begin(); it != actors_.map_.end(); ++it)
	{
		it->second->draw(window);
	}
}
void	glutpp::scene::resize(int w, int h) {
}





