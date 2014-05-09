#include <stdio.h>

#include <Nebula/Graphics/window/window.hpp>
#include <Nebula/renderable.hpp>
#include <Nebula/scene/desc.hpp>
#include <Nebula/scene/scene.hpp>
#include <Nebula/Actor/Base.hpp>

#include <Nebula/Graphics/light/light.hpp>
#include <Nebula/Graphics/glsl/program.hpp>
#include <Nebula/Graphics/Camera/Projection/Perspective.hpp>


Neb::Scene::scene::scene() {
	GLUTPP_DEBUG_0_FUNCTION;
}
Neb::Scene::scene::~scene() {
	GLUTPP_DEBUG_0_FUNCTION;
}
void Neb::Scene::scene::i(int ni) {
	GLUTPP_DEBUG_0_FUNCTION;

	//desc_->raw_.i_ = ni;
	//desc_->i_ = ni;
	i_ = ni;
}
int Neb::Scene::scene::i() {
	return i_;
}
unsigned int Neb::Scene::scene::f() {
	return raw_->flag_;
}
void Neb::Scene::scene::f(unsigned int flag) {
	raw_->flag_ = flag;
}
void Neb::Scene::scene::init(Neb::Scene::desc_s desc) {
	GLUTPP_DEBUG_0_FUNCTION;
	//renderable_ = renderable;
}
void Neb::Scene::scene::release() {
	GLUTPP_DEBUG_0_FUNCTION;	
}
physx::PxMat44		Neb::Scene::scene::get_pose() {
	return physx::PxMat44();
}
void Neb::Scene::scene::render(double time,
		std::shared_ptr<Neb::Camera::View::Base<float> > view,
		std::shared_ptr<Neb::Camera::Projection::Base> proj,
		Neb::window::window_s window) {

	GLUTPP_DEBUG_1_FUNCTION;

	assert(view);
	assert(proj);

	auto p = Neb::master::Global()->use_program(Neb::program_name::e::LIGHT);


	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);

	
	view->load();
	proj->load();

	int i = 0;
	for(auto it = actors_.map_.begin(); it != actors_.map_.end(); ++it)
	{
		it->second->load_lights(i, physx::PxMat44());
	}

	p->get_uniform_scalar("light_count")->load(i);

	//printf("%i\n",i);

	draw(window);
}
void Neb::Scene::scene::draw(Neb::window::window_s window) {

	GLUTPP_DEBUG_1_FUNCTION;

	for(auto it = actors_.map_.begin(); it != actors_.map_.end(); ++it)
	{
		it->second->draw(window, physx::PxMat44());
	}
}
void Neb::Scene::scene::resize(int w, int h) {
}


