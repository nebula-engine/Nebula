#include <neb/config.h>
#include <neb/timer/actor.h>
#include <neb/app.h>
#include <neb/scene/scene.h>
#include <neb/shape.h>

#include <glutpp/actor/desc.h>

#include <neb/actor/Base.h>
#include <neb/actor/empty.h>

neb::actor::Base::Base(
		std::shared_ptr<neb::scene::scene> scene,
		std::shared_ptr<neb::actor::Base> actor):
	glutpp::actor::actor(scene, actor)
{
	NEBULA_DEBUG_0_FUNCTION;
	
	assert(scene);
}
neb::actor::Base::~Base() {
	NEBULA_DEBUG_0_FUNCTION;
}
void neb::actor::Base::init(glutpp::actor::desc_s desc) {
	NEBULA_DEBUG_0_FUNCTION;
	
	glutpp::actor::actor::init(desc);
	
	create_physics();
	create_children(desc);
	create_shapes(desc);
	init_physics();
}
void neb::actor::Base::release() {

	glutpp::actor::actor::release();
	
	conn_.key_fun_.reset();
}
void neb::actor::Base::create_children(glutpp::actor::desc_s desc) {
	NEBULA_DEBUG_0_FUNCTION;

	// create children
	for(auto it = desc->get_actors()->vec_.begin(); it != desc->get_actors()->vec_.end(); ++it)
	{
		create_actor(std::get<0>(*it));
	}
	
	
}
neb::actor::Base_s neb::actor::Base::create_actor(glutpp::actor::desc_s desc) {
	
	printf("%s\n",__PRETTY_FUNCTION__);
	
	auto scene = get_scene();//std::dynamic_pointer_cast<neb::scene::scene>(shared_from_this());
	
	auto me = std::dynamic_pointer_cast<neb::actor::Base>(shared_from_this());
	
	neb::actor::Base_s actor;
	
	switch(desc->get_raw()->type_)
	{
		case glutpp::actor::RIGID_DYNAMIC:
			actor.reset(new neb::actor::Rigid_Dynamic(scene, me));
			// = Create_Rigid_Dynamic(ad);
			break;
		case glutpp::actor::RIGID_STATIC:
			actor.reset(new neb::actor::Rigid_Static(scene, me));
			// = Create_Rigid_Static(ad);
			break;
		case glutpp::actor::PLANE:
			//actor = Create_Rigid_Static_Plane(ad);
			printf("not implemented\n");
			abort();
			break;
		case glutpp::actor::CONTROLLER:
			printf("not implemented\n");
			abort();
			//actor = Create_Controller(ad);
			break;
		case glutpp::actor::EMPTY:
			actor.reset(new neb::actor::empty(scene, me));
			break;
		default:
			abort();
	}
	
	actor->init(desc);
	
	return actor;
}
neb::actor::Base_s neb::actor::Base::create_actor_local(glutpp::actor::desc_s desc) {
	auto actor = create_actor(desc);
	actors_.push_back(actor);
	return actor;
}
neb::actor::Base_s neb::actor::Base::create_actor_remote(
		glutpp::actor::addr_s addr,
		glutpp::actor::desc_s desc) {
	
	auto vec = addr->get_vec();
	assert(!vec->vec_.empty());
	int i;
	neb::actor::Base_s actor;
	
	if(vec->vec_.size() > 1)
	{
		// vector size > 1
		// actor is under another actor
		i = vec->vec_.front();
		vec->vec_.pop_front();
		
		auto parent_actor = get_actor(i);
		assert(parent_actor);
		
		actor = parent_actor->create_actor_remote(addr, desc);
	}
	else
	{
		// vector size == 1
		// actor is directly under this
		actor = create_actor(desc);
		actors_[desc->get_id()->i_];
	}
	
	return actor;
}
std::shared_ptr<neb::app> neb::actor::Base::get_app() {

	auto scene = get_scene();

	assert(!scene->app_.expired());
	
	return scene->app_.lock();
}
std::shared_ptr<neb::scene::scene> neb::actor::Base::get_scene() {

	assert(!scene_.expired());
	
	auto scene = std::dynamic_pointer_cast<neb::scene::scene>(scene_.lock());

	return scene;
}
neb::actor::Base_s neb::actor::Base::get_actor(int i) {
	auto it = actors_.find(i);
	neb::actor::Base_s a;
	if(it == actors_.end())
	{
		return a;
	}
	else
	{
		a = std::dynamic_pointer_cast<neb::actor::Base>(it->second);
		return a;
	}
}
neb::actor::Base_s neb::actor::Base::get_actor(glutpp::actor::addr_s addr) {
	
	auto vec = addr->get_vec();
	assert(vec);
	assert(!vec->vec_.empty());
	
	int i = vec->vec_.front();
	vec->vec_.pop_front();
	
	auto actor = get_actor(i);
	assert(actor);
	
	if(!vec->vec_.empty())
	{
		return actor->get_actor(addr);
	}
	
	return actor;
}
void	neb::actor::Base::set_pose(math::transform pose) {

	raw_.pose_ = pose;
}
int	neb::actor::Base::fire() {

	printf("%s\n", __PRETTY_FUNCTION__);

	glutpp::actor::desc_s desc = get_projectile();

	auto scene = get_scene();

	//auto me = std::dynamic_pointer_cast<neb::actor::Actor>(shared_from_this());

	auto a = scene->create_actor_local(desc);

	neb::timer::actor_s t(new neb::timer::actor(a, neb::timer::actor::type::RELEASE, scene->last_ + 5.0));

	scene->timer_set_.set_.insert(t);

	return 1;
}
glutpp::actor::desc_s neb::actor::Base::get_projectile() {

	NEBULA_DEBUG_0_FUNCTION;

	abort();

	return glutpp::actor::desc_s();
}
void	neb::actor::Base::step_remote(double) {
}
void neb::actor::Base::create_shapes(glutpp::actor::desc_s desc) {
	NEBULA_DEBUG_0_FUNCTION;

	auto me = std::dynamic_pointer_cast<neb::actor::Base>(shared_from_this());

	std::shared_ptr<neb::shape> shape;

	for(auto it = desc->get_shapes()->vec_.begin(); it != desc->get_shapes()->vec_.end(); ++it)
	{
		glutpp::shape::desc_s sd = std::get<0>(*it);

		shape.reset(new neb::shape(me));

		shape->init(sd);

		shapes_.push_back(shape);
	}
}
void neb::actor::Base::connect(glutpp::window::window_s window) {
	
	window_ = window;
	
	auto me = std::dynamic_pointer_cast<neb::actor::Base>(shared_from_this());
	
	conn_.key_fun_ = window->sig_.key_fun_.connect(std::bind(
				&neb::actor::Base::key_fun,
				me,
				std::placeholders::_1,
				std::placeholders::_2,
				std::placeholders::_3,
				std::placeholders::_4));

}
int neb::actor::Base::key_fun(int key, int scancode, int action, int mods) {

	switch(action) {
		case GLFW_PRESS:
			switch(key) {
				case GLFW_KEY_SPACE:
					fire();
					return 1;
				default:
					return 0;
			}
		case GLFW_RELEASE:
			switch(key) {
				default:
					return 0;
			}
	}

	return 0;
}
neb::actor::rigid_body::rigid_body_s neb::actor::Base::to_rigid_body() {
	return std::dynamic_pointer_cast<neb::actor::rigid_body::rigid_body>(shared_from_this());
}



