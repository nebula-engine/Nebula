

#include <Nebula/debug.hpp>
#include <Nebula/Typed.hpp>
#include <Nebula/config.hpp>
#include <Nebula/timer/Actor/Base.hpp>
#include <Nebula/app.hpp>
#include <Nebula/scene/scene.hpp>
#include <Nebula/shape/Physical.hpp>
#include <Nebula/Actor/Base.hpp>
#include <Nebula/Actor/empty.hpp>
#include <Nebula/Actor/Types.hpp>
#include <Nebula/Actor/Util/desc.hpp>


Neb::Actor::Base::Base(Neb::Actor::parent_w parent): parent_(parent) {
	NEBULA_ACTOR_BASE_FUNC;
}
Neb::Actor::Base::~Base() {
	NEBULA_ACTOR_BASE_FUNC;
}
void Neb::Actor::Base::init(Neb::Actor::desc_w desc) {
	NEBULA_ACTOR_BASE_FUNC;
	
	raw_.reset();
	raw_.swap(desc->raw_wrapper_.ptr_);


	create_physics();
	create_children(desc);
	create_shapes(desc);
	init_physics();
}
void Neb::Actor::Base::release() {

	for(auto it = actors_.begin(); it != actors_.end(); ++it) {
		it->second->release();
	}
	actors_.clear();


	conn_.key_fun_.disconnect();
}
void Neb::Actor::Base::create_children(Neb::Actor::desc_w desc) {
	NEBULA_ACTOR_BASE_FUNC;

	// create children
	for(auto it = desc->actors_.begin(); it != desc->actors_.end(); ++it)
	{
		create_actor(*it);
	}


}
Neb::Actor::Base_w		Neb::Actor::Base::create_actor(Neb::Actor::desc_w desc) {

	printf("%s\n",__PRETTY_FUNCTION__);

	auto scene = get_scene();//std::dynamic_pointer_cast<Neb::scene::scene>(shared_from_this());

	auto me = std::dynamic_pointer_cast<Neb::Actor::Base>(shared_from_this());

	Neb::Actor::Base_s actor;

	switch(desc->get_raw()->type_)
	{
		case Neb::Actor::type::e::RIGID_DYNAMIC:
			actor.reset(new Neb::Actor::Rigid_Dynamic(me));
			// = Create_Rigid_Dynamic(ad);
			break;
		case Neb::Actor::type::e::RIGID_STATIC:
			actor.reset(new Neb::Actor::Rigid_Static(me));
			// = Create_Rigid_Static(ad);
			break;
		case Neb::Actor::type::e::PLANE:
			//actor = Create_Rigid_Static_Plane(ad);
			printf("not implemented\n");
			abort();
			break;
		case Neb::Actor::type::e::CONTROLLER:
			printf("not implemented\n");
			abort();
			//actor = Create_Controller(ad);
			break;
		case Neb::Actor::type::e::EMPTY:
			actor.reset(new Neb::Actor::empty(me));
			break;
		default:
			abort();
	}

	actor->init(desc);

	return actor;
}
Neb::Actor::Base_s Neb::Actor::Base::create_actor_local(Neb::Actor::desc_s desc) {
	auto actor = create_actor(desc);
	actors_.push_back(actor);
	return actor;
}
Neb::Actor::Base_s Neb::Actor::Base::create_actor_remote(Neb::Actor::addr_s addr, Neb::actor::desc_s desc) {

	auto vec = addr->get_vec();
	assert(!vec->vec_.empty());
	int i;
	Neb::Actor::Base_s actor;

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
std::shared_ptr<Neb::app> Neb::Actor::Base::get_app() {
	NEBULA_ACTOR_BASE_FUNC;

	auto scene = get_scene();

	assert(!scene->app_.expired());

	return scene->app_.lock();
}
std::shared_ptr<Neb::scene::scene> Neb::Actor::Base::get_scene() {
	NEBULA_ACTOR_BASE_FUNC;

	auto scene = std::dynamic_pointer_cast<Neb::scene::scene>(Neb::Actor::actor::get_scene());

	return scene;
}
Neb::Actor::Base_s Neb::Actor::Base::get_actor(int i) {
	NEBULA_ACTOR_BASE_FUNC;

	auto it = actors_.find(i);
	Neb::Actor::Base_s a;
	if(it == actors_.end())
	{
		return a;
	}
	else
	{
		a = std::dynamic_pointer_cast<Neb::Actor::Base>(it->second);
		return a;
	}
}
Neb::Actor::raw_s Neb::Actor::Base::get_raw_base() {
	NEBULA_ACTOR_BASE_FUNC;
	auto raw = get_raw();
	auto raw_base = std::dynamic_pointer_cast<Neb::Actor::raw>(raw);
	assert(raw_base);
	return raw_base;
}
Neb::Actor::Base_s Neb::Actor::Base::get_actor(Neb::Actor::addr_s addr) {
	NEBULA_ACTOR_BASE_FUNC;

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
int	Neb::Actor::Base::fire() {
	NEBULA_ACTOR_BASE_FUNC;

	printf("%s\n", __PRETTY_FUNCTION__);

	get_scene()->fire(isBase());

	return 1;
}
Neb::Actor::desc_s Neb::Actor::Base::get_projectile() {
	NEBULA_ACTOR_BASE_FUNC;

	abort();

	return Neb::Actor::desc_s();
}
void Neb::Actor::Base::step_local(double time) {
	NEBULA_ACTOR_BASE_FUNC;

	Neb::Actor::actor::step(time);
}
void Neb::Actor::Base::step_remote(double time) {
	NEBULA_ACTOR_BASE_FUNC;

	Neb::Actor::actor::step(time);
}
void Neb::Actor::Base::create_shapes(Neb::Actor::desc_s desc) {
	NEBULA_ACTOR_BASE_FUNC;

	auto me = std::dynamic_pointer_cast<Neb::Actor::Base>(shared_from_this());

	Neb::shape::shape_s shape;

	for(auto it = desc->get_shapes()->vec_.begin(); it != desc->get_shapes()->vec_.end(); ++it)
	{
		Neb::shape::desc_s sd = std::get<0>(*it);
		assert(sd);

		shape.reset(new Neb::shape::shape(me));

		shape->init(sd);

		shapes_.push_back(shape);
	}
}
void Neb::Actor::Base::hit() {
	
	physx::PxU32 w2 = get_raw()->filter_data_.simulation_.word2;
	
	if(w2 & Neb::filter::type::PROJECTILE)
	{
		set(Neb::Actor::actor::flag::e::SHOULD_RELEASE);
	}
	
	if(any(Neb::Actor::actor::flag::e::DESTRUCTIBLE))
	{
		damage(0.1);
	}
}
void Neb::Actor::Base::damage(float h) {
	get_raw_base()->health_ -= h;
	if(get_raw_base()->health_ < 0)
	{
		set(Neb::Actor::actor::flag::e::SHOULD_RELEASE);
	}
}
void Neb::Actor::Base::connect(Neb::window::window_s window) {

	window_ = window;

	auto me = std::dynamic_pointer_cast<Neb::Actor::Base>(shared_from_this());

	conn_.key_fun_ = window->sig_.key_fun_.connect(std::bind(
				&Neb::Actor::Base::key_fun,
				me,
				std::placeholders::_1,
				std::placeholders::_2,
				std::placeholders::_3,
				std::placeholders::_4));

}
int Neb::Actor::Base::key_fun(int key, int scancode, int action, int mods) {

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
Neb::Actor::Base_s			Neb::Actor::Base::isBase() {
	return std::dynamic_pointer_cast<Neb::Actor::Base>(shared_from_this());
}
Neb::Actor::RigidActor_s		Neb::Actor::Base::isRigidActor() {
	return std::dynamic_pointer_cast<Neb::Actor::RigidActor>(shared_from_this());
}
Neb::Actor::RigidBody::RigidBody_s	Neb::Actor::Base::isRigidBody() {
	return std::dynamic_pointer_cast<Neb::Actor::RigidBody::RigidBody>(shared_from_this());
}



