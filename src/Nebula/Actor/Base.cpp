

#include <Nebula/debug.hpp>
#include <Nebula/Typed.hpp>
#include <Nebula/Types.hpp>
#include <Nebula/config.hpp> // Nebula/config.hpp.in
#include <Nebula/timer/Actor/Base.hpp>
#include <Nebula/app.hpp>
#include <Nebula/scene/scene.hpp>
#include <Nebula/shape/Physical.hpp>

#include <Nebula/Actor/Base.hpp>
#include <Nebula/Actor/Rigid_Actor.hpp>
#include <Nebula/Actor/rigid_body/rigid_body.hpp>
#include <Nebula/Actor/empty.hpp>
#include <Nebula/Actor/Types.hpp>
#include <Nebula/Actor/Util/desc.hpp>

#include <Nebula/Filter.hpp>
#include <Nebula/Graphics/window/window.hpp>

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
/*Neb::Actor::Base_w		Neb::Actor::Base::create_actor(Neb::Actor::desc_w desc) {

	printf("%s\n",__PRETTY_FUNCTION__);

	auto scene = get_scene();//std::dynamic_pointer_cast<Neb::Scene::scene>(shared_from_this());

	//auto me = std::dynamic_pointer_cast<Neb::Actor::Base>(shared_from_this());
	auto me = isBase();

	Neb::Actor::Base_w actor;


	switch(desc->get_raw()->type_) {
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
}*/
Neb::Actor::Base_w		Neb::Actor::Base::create_actor_local(Neb::Actor::desc_w desc) {

	long int hash_code = desc->raw_wrapper_.ptr_->type_.val_;
	
	Neb::Actor::Base_u actor(Neb::master::global()->factories_.actor_base_->alloc(hash_code));
	
	actors_.push_back(actor);

	return actor;
}
Neb::Actor::Base_w		Neb::Actor::Base::create_actor_remote(Neb::Actor::addr_w addr, Neb::Actor::desc_w desc) {

	//auto vec = addr->get_vec();
	assert(!addr->vec_.empty());
	int i;
	Neb::Actor::Base_w actor;

	if(addr->vec_.size() > 1) {
		// vector size > 1
		// actor is under another actor
		i = addr->vec_.front();
		addr->vec_.pop_front();

		auto parent_actor = get_actor(i);
		assert(parent_actor);

		actor = parent_actor->create_actor_remote(addr, desc);
	} else {
		// vector size == 1
		// actor is directly under this
		
		long int hash_code = desc->raw_wrapper_.ptr_->type_.val_;
		Neb::unique_ptr<Neb::Actor::Base> actor(Neb::master::global()->factories_.actor_base_->alloc(hash_code));

		//
		actors_.map_.emplace(desc->i_, std::move(actor));
	}

	return actor;
}
Neb::app_w			Neb::Actor::Base::get_app() {
	NEBULA_ACTOR_BASE_FUNC;

	auto scene = get_scene();

	//assert(!scene->app_.expired());
	
	return scene->get_app();
}
Neb::Scene::scene_w		Neb::Actor::Base::get_scene() {
	NEBULA_ACTOR_BASE_FUNC;

	return parent_->getScene();
}
Neb::Actor::Base_w		Neb::Actor::Base::get_actor(int i) {
	NEBULA_ACTOR_BASE_FUNC;

	auto it = actors_.find(i);
	Neb::Actor::Base_w a;
	if(it == actors_.end())
	{
		return a;
	}
	else
	{
		return it->second;
	}
}
Neb::Actor::Base_w Neb::Actor::Base::get_actor(Neb::Actor::addr_w addr) {
	NEBULA_ACTOR_BASE_FUNC;

	//auto vec = addr->get_vec();
	//assert(vec);
	assert(!addr->vec_.empty());

	int i = addr->vec_.front();
	addr->vec_.pop_front();

	auto actor = get_actor(i);
	assert(actor);

	if(!addr->vec_.empty())
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
void Neb::Actor::Base::step_local(double time) {
	NEBULA_ACTOR_BASE_FUNC;

	for(auto it = shapes_.begin(); it != shapes_.end(); ++it) {
		it->second->step(time);
	}


}
void Neb::Actor::Base::step_remote(double time) {
	NEBULA_ACTOR_BASE_FUNC;

	for(auto it = shapes_.begin(); it != shapes_.end(); ++it) {
		it->second->step(time);
	}
}
void Neb::Actor::Base::create_shapes(Neb::Actor::desc_w desc) {
	NEBULA_ACTOR_BASE_FUNC;

	//auto me = std::dynamic_pointer_cast<Neb::Actor::Base>(shared_from_this());
	auto me = isBase();

	Neb::Shape::shape_u shape;

	for(auto it = desc->shapes_.begin(); it != desc->shapes_.end(); ++it) {
		Neb::Shape::desc_w sd = *it;
		assert(sd);
		
		long int hash_code;// = desc->raw_->hash_code_;

		shape.reset(Neb::master::global()->factories_.shape_base_->alloc(hash_code, me));
		
		shape->init(sd);
		
		shapes_.push_back(shape);
	}
}
void Neb::Actor::Base::hit() {

	physx::PxU32 w2 = raw_->simulation_.word2;
	
	if(w2 & Neb::Filter::Filter::PROJECTILE) {
		set(Neb::Actor::Base::flag::e::SHOULD_RELEASE);
	}
	
	if(any(Neb::Actor::Base::flag::e::DESTRUCTIBLE)) {
		damage(0.1);
	}
}
void Neb::Actor::Base::damage(float h) {
	raw_->health_ -= h;
	if(raw_->health_ < 0) {
		set(Neb::Actor::Base::flag::e::SHOULD_RELEASE);
	}
}
void		Neb::Actor::Base::connect(Neb::window::window_w window) {

	window_ = window;

	//auto me = std::dynamic_pointer_cast<Neb::Actor::Base>(shared_from_this());
	auto me = isBase();

	boost::function<int(int,int,int,int)> f(boost::bind(
				&Neb::Actor::Base::key_fun,
				me.ptr_,
				_1,
				_2,
				_3,
				_4));

	conn_.key_fun_ = window->sig_.key_fun_.connect(boost::bind(
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
Neb::Actor::Base_w			Neb::Actor::Base::isBase() {
	return boost::dynamic_pointer_cast<Neb::Actor::Base>(shared_from_this());
}
Neb::Actor::RigidActor_w		Neb::Actor::Base::isRigidActor() {
	return boost::dynamic_pointer_cast<Neb::Actor::RigidActor>(shared_from_this());
}
Neb::Actor::RigidBody::RigidBody_w	Neb::Actor::Base::isRigidBody() {
	return boost::dynamic_pointer_cast<Neb::Actor::RigidBody::RigidBody>(shared_from_this());
}




