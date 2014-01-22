#include <stdio.h>

#include <glutpp/window/window.h>
#include <glutpp/renderable.h>
#include <glutpp/scene/desc.h>
#include <glutpp/scene/scene.h>
#include <glutpp/actor/actor.h>
#include <glutpp/light/light.h>

#include <glutpp/glsl/program.h>


glutpp::scene::scene::scene() {
	GLUTPP_DEBUG_0_FUNCTION;
}
glutpp::scene::scene::~scene() {
	GLUTPP_DEBUG_0_FUNCTION;
}
void glutpp::scene::scene::i(int ni) {
	GLUTPP_DEBUG_0_FUNCTION;

	//desc_->raw_.i_ = ni;
	//desc_->i_ = ni;
	i_ = ni;
}
int glutpp::scene::scene::i() {
	return i_;
}
unsigned int glutpp::scene::scene::f() {
	return raw_.flag_;
}
void glutpp::scene::scene::f(unsigned int flag) {
	raw_.flag_ = flag;
}
void glutpp::scene::scene::init(glutpp::scene::desc_s desc) {
	GLUTPP_DEBUG_0_FUNCTION;
	//renderable_ = renderable;
}
void glutpp::scene::scene::release() {
	GLUTPP_DEBUG_0_FUNCTION;	
}
math::mat44 glutpp::scene::scene::get_pose() {
	return math::mat44();
}
void glutpp::scene::scene::render(double time,
		std::shared_ptr<glutpp::camera> camera,
		glutpp::window::window_s window) {

	GLUTPP_DEBUG_1_FUNCTION;

	assert(camera);

	auto p = glutpp::__master.use_program(glutpp::program_name::e::LIGHT);


	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);

	camera->load();

	int i = 0;
	for(auto it = actors_.map_.begin(); it != actors_.map_.end(); ++it)
	{
		it->second->load_lights(i, math::mat44());
	}

	p->get_uniform(glutpp::uniform_name::LIGHT_COUNT)->load(i);

	//printf("%i\n",i);

	draw(window);
}
void glutpp::scene::scene::draw(glutpp::window::window_s window) {

	GLUTPP_DEBUG_1_FUNCTION;

	for(auto it = actors_.map_.begin(); it != actors_.map_.end(); ++it)
	{
		it->second->draw(window, math::mat44());
	}
}
void glutpp::scene::scene::resize(int w, int h) {
}


