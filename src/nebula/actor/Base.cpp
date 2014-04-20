
#include <nebula/config.hpp>
#include <nebula/timer/actor.hpp>
#include <nebula/app.hpp>
#include <nebula/scene/scene.hpp>
#include <nebula/shape.hpp>
#include <nebula/actor/Base.hpp>
#include <nebula/actor/empty.hpp>

#include <gru/actor/desc.hpp>


neb::actor::Base::Base(glutpp::parent_s parent):
	glutpp::actor::actor(parent)
{
	NEBULA_DEBUG_0_FUNCTION;
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
		case glutpp::actor::type::e::RIGID_DYNAMIC:
			actor.reset(new neb::actor::Rigid_Dynamic(me));
			// = Create_Rigid_Dynamic(ad);
			break;
		case glutpp::actor::type::e::RIGID_STATIC:
			actor.reset(new neb::actor::Rigid_Static(me));
			// = Create_Rigid_Static(ad);
			break;
		case glutpp::actor::type::e::PLANE:
			//actor = Create_Rigid_Static_Plane(ad);
			printf("not implemented\n");
			abort();
			break;
		case glutpp::actor::type::e::CONTROLLER:
			printf("not implemented\n");
			abort();
			//actor = Create_Controller(ad);
			break;
		case glutpp::actor::type::e::EMPTY:
			actor.reset(new neb::actor::empty(me));
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
neb::actor::Base_s neb::actor::Base::create_actor_remote(glutpp::actor::addr_s addr, glutpp::actor::desc_s desc) {

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
	NEBULA_DEBUG_1_FUNCTION;

	auto scene = get_scene();

	assert(!scene->app_.expired());

	return scene->app_.lock();
}
std::shared_ptr<neb::scene::scene> neb::actor::Base::get_scene() {
	NEBULA_DEBUG_1_FUNCTION;

	auto scene = std::dynamic_pointer_cast<neb::scene::scene>(glutpp::actor::actor::get_scene());

	return scene;
}
neb::actor::Base_s neb::actor::Base::get_actor(int i) {
	NEBULA_DEBUG_1_FUNCTION;

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
neb::actor::raw_s neb::actor::Base::get_raw_base() {
	NEBULA_DEBUG_1_FUNCTION;
	auto raw = get_raw();
	auto raw_base = std::dynamic_pointer_cast<neb::actor::raw>(raw);
	assert(raw_base);
	return raw_base;
}
neb::actor::Base_s neb::actor::Base::get_actor(glutpp::actor::addr_s addr) {
	NEBULA_DEBUG_1_FUNCTION;

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
int	neb::actor::Base::fire() {
	NEBULA_DEBUG_1_FUNCTION;

	printf("%s\n", __PRETTY_FUNCTION__);

	get_scene()->fire(to_base());

	return 1;
}
glutpp::actor::desc_s neb::actor::Base::get_projectile() {
	NEBULA_DEBUG_0_FUNCTION;

	abort();

	return glutpp::actor::desc_s();
}
void neb::actor::Base::step_local(double time) {
	NEBULA_DEBUG_1_FUNCTION;

	glutpp::actor::actor::step(time);
}
void neb::actor::Base::step_remote(double time) {
	NEBULA_DEBUG_1_FUNCTION;

	glutpp::actor::actor::step(time);
}
void neb::actor::Base::create_shapes(glutpp::actor::desc_s desc) {
	NEBULA_DEBUG_0_FUNCTION;

	auto me = std::dynamic_pointer_cast<neb::actor::Base>(shared_from_this());

	neb::shape::shape_s shape;

	for(auto it = desc->get_shapes()->vec_.begin(); it != desc->get_shapes()->vec_.end(); ++it)
	{
		glutpp::shape::desc_s sd = std::get<0>(*it);
		assert(sd);

		shape.reset(new neb::shape::shape(me));

		shape->init(sd);

		shapes_.push_back(shape);
	}
}
void neb::actor::Base::hit() {
	
	physx::PxU32 w2 = get_raw()->filter_data_.simulation_.word2;
	
	if(w2 & glutpp::filter::type::PROJECTILE)
	{
		set(glutpp::actor::actor::flag::e::SHOULD_RELEASE);
	}
	
	if(any(glutpp::actor::actor::flag::e::DESTRUCTIBLE))
	{
		damage(0.1);
	}
}
void neb::actor::Base::damage(float h) {
	get_raw_base()->health_ -= h;
	if(get_raw_base()->health_ < 0)
	{
		set(glutpp::actor::actor::flag::e::SHOULD_RELEASE);
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
				case GLFW_KEY_ESCAPE:
					get_app()->set_should_release();
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
neb::actor::Base_s neb::actor::Base::to_base() {
	return std::dynamic_pointer_cast<neb::actor::Base>(shared_from_this());
}
neb::actor::rigid_body::rigid_body_s neb::actor::Base::to_rigid_body() {
	return std::dynamic_pointer_cast<neb::actor::rigid_body::rigid_body>(shared_from_this());
}



