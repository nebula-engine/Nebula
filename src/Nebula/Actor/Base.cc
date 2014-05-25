

#include <Nebula/debug.hh>

//#include <Nebula/Util/Typed.hh>

#include <Nebula/Types.hh>
#include <Nebula/config.hh> // Nebula/config.hpp.in
#include <Nebula/timer/Actor/Base.hpp>
#include <Nebula/App/Base.hh>
#include <Nebula/Scene/Base.hh>
#include <Nebula/Shape/Physical.hh>
#include <Nebula/Signals.hh>

#include <Nebula/Actor/Base.hh>
#include <Nebula/Actor/RigidActor/Base.hh>
#include <Nebula/Actor/RigidBody/Base.hh>
#include <Nebula/Actor/empty.hh>
#include <Nebula/Actor/Util/Types.hh>

#include <Nebula/Filter.hh>
#include <Nebula/Graphics/Window/Base.hh>


Neb::Actor::Base::Base(Neb::Actor::Util::Parent_s parent): parent_(parent) {
	NEBULA_ACTOR_BASE_FUNC;
	
	sig_release_.connect(
		std::bind(
			&Neb::Actor::Base::release,
			this
			));
}
Neb::Actor::Base::~Base() {
	NEBULA_ACTOR_BASE_FUNC;
}
void		Neb::Actor::Base::init() {
}
Neb::Actor::Util::Parent_s	Neb::Actor::Base::getParent() {
	return parent_;
}
physx::PxTransform		Neb::Actor::Base::getPose() {
	return pose_;
}
physx::PxTransform		Neb::Actor::Base::getPoseGlobal() {
	NEBULA_ACTOR_BASE_FUNC;

	physx::PxTransform m;

	if(!parent_) {
		m = parent_->getPoseGlobal() * getPose();
	} else {
		m = getPose();
	}

	return m;
}
void		Neb::Actor::Base::setPose(physx::PxTransform pose) {
	pose_ = pose;
	
	flag_.set(Neb::Actor::Util::Flag::E::SHOULD_UPDATE);
	
	notify_foundation_change_pose();
}
void Neb::Actor::Base::notify_foundation_change_pose() {

	typedef Neb::Util::Parent<Neb::Actor::Base> A;
	typedef Neb::Util::Parent<Neb::Shape::Base> S;
	
	A::map_.for_each([] (A::map_type::const_iterator it) {
		it->second.ptr_->notify_foundation_change_pose();
	});

	S::map_.for_each([] (S::map_type::const_iterator it) {
		it->second.ptr_->notify_foundation_change_pose();
	});

}
void		Neb::Actor::Base::load_lights(int& i, physx::PxMat44 space) {
	NEBULA_ACTOR_BASE_FUNC;

	space = space * physx::PxMat44(pose_);
	
	typedef Neb::Util::Parent<Neb::Actor::Base> A;
	typedef Neb::Util::Parent<Neb::Shape::Base> S;
	
	A::map_.for_each([&] (A::map_type::const_iterator it) {
		it->second.ptr_->load_lights(i, space);
	});
	
	S::map_.for_each([&] (S::map_type::const_iterator it) {
		it->second.ptr_->load_lights(i, space);
	});

}
void		Neb::Actor::Base::draw(Neb::Graphics::Window::Base_s window, physx::PxTransform space) {
	NEBULA_ACTOR_BASE_FUNC;

	space = space * pose_;
	
	typedef Neb::Util::Parent<Neb::Actor::Base> A;
	typedef Neb::Util::Parent<Neb::Shape::Base> S;
	
	A::map_.for_each([&] (A::map_type::const_iterator it) {
		it->second.ptr_->draw(window, space);
	});

	S::map_.for_each([&] (S::map_type::const_iterator it) {
		it->second.ptr_->draw(window, space);
	});


}
/*void Neb::Actor::Base::init(Neb::Actor::desc_w desc) {
  NEBULA_ACTOR_BASE_FUNC;

  raw_.reset();
  raw_.swap(desc->raw_wrapper_.ptr_);


  create_physics();
  create_children(desc);
  create_shapes(desc);
  init_physics();
  }*/
void		Neb::Actor::Base::release() {

	Neb::Util::Parent<Neb::Actor::Base>::clear();
	Neb::Util::Parent<Neb::Shape::Base>::clear();

	//conn_.key_fun_.disconnect();
}
/*void Neb::Actor::Base::create_children(Neb::Actor::desc_w desc) {
  NEBULA_ACTOR_BASE_FUNC;

// create children
for(auto it = desc->actors_.begin(); it != desc->actors_.end(); ++it)
{
create_actor(*it);
}
}*/
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
/*Neb::Actor::Base_w		Neb::Actor::Base::create_actor_local(Neb::Actor::desc_w desc) {

  long int hash_code = desc->raw_wrapper_.ptr_->type_.val_;

  Neb::Actor::Base_u actor(Neb::master::global()->factories_.actor_base_->alloc(hash_code));

  actors_.push_back(actor);

  return actor;
  }*/
/*Neb::Actor::Base_w		Neb::Actor::Base::create_actor_remote(Neb::Actor::addr_w addr, Neb::Actor::desc_w desc) {

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
}*/

int	Neb::Actor::Base::fire() {
	NEBULA_ACTOR_BASE_FUNC;

	printf("%s\n", __PRETTY_FUNCTION__);

	getScene()->fire(isActorBase());

	return 1;
}
void		Neb::Actor::Base::step(double const & time, double const & dt) {
	NEBULA_ACTOR_BASE_FUNC;

	typedef Neb::Util::Parent<Neb::Actor::Base> A;
	typedef Neb::Util::Parent<Neb::Shape::Base> S;
	
	A::map_.for_each([&] (A::map_type::const_iterator it) {
		it->second.ptr_->step(time, dt);
	});
	
	S::map_.for_each([&] (S::map_type::const_iterator it) {
		it->second.ptr_->step(time, dt);
	});

}
/*void Neb::Actor::Base::create_shapes(Neb::Actor::desc_w desc) {
  NEBULA_ACTOR_BASE_FUNC;

//auto me = std::dynamic_pointer_cast<Neb::Actor::Base>(shared_from_this());
auto me = isBase();

Neb::Shape::shape_u shape;

for(auto it = desc->shapes_.begin(); it != desc->shapes_.end(); ++it) {
Neb::Shape::desc_w sd = *it;
assert(sd);

long int hash_code = sd->raw_wrapper_.ptr_->hash_code_;

shape.reset(Neb::master::global()->factories_.shape_base_->alloc(hash_code, me));

shape->init(sd);

shapes_.push_back(shape);
}
}*/
void Neb::Actor::Base::hit() {

	physx::PxU32 w2 = simulation_.word2;
	
	if(w2 & Neb::Filter::Filter::PROJECTILE) {
		parent_->release(i_);
		//set(Neb::Actor::Base::flag::e::SHOULD_RELEASE);
	}

	if(flag_.any(Neb::Actor::Util::Flag::E::DESTRUCTIBLE)) {
		damage(0.1);
	}
}
void Neb::Actor::Base::damage(float h) {
	health_ -= h;
	if(health_ < 0) {
		parent_->release(i_);
	}
}
void		Neb::Actor::Base::connect(Neb::Graphics::Window::Base_s window) {

	//window_ = window;

	//auto me = std::dynamic_pointer_cast<Neb::Actor::Base>(shared_from_this());
	auto me = isActorBase();

	//auto shared = sharedBase();

	//conn_.key_fun_.reset(new Neb::weak_function<int,int,int,int,int>(&Neb::Actor::Base::key_fun));

	assert(window);

	auto c = window->sig_.key_fun_.connect(
			Neb::Signals::KeyFun::slot_type(
				&Neb::Actor::Base::key_fun,
				me.get(),
				_1,
				_2,
				_3,
				_4
				).track_foreign(me)
			);

}
int Neb::Actor::Base::key_fun(int key, int scancode, int action, int mods) {

	switch(action) {
		case GLFW_PRESS:
			switch(key) {
				case GLFW_KEY_SPACE:
					fire();
					return 1;
				case GLFW_KEY_ESCAPE:
					Neb::App::Base::globalBase()->set_should_release();
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




