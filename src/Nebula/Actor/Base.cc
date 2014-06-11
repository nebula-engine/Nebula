

#include <Nebula/debug.hh>

//#include <Nebula/Util/Typed.hh>

#include <Nebula/Types.hh>
#include <Nebula/config.hh> // Nebula/config.hpp.in
#include <Nebula/timer/Actor/Base.hpp>
//#include <Nebula/App/Base.hh>
#include <Nebula/Scene/Base.hh>
#include <Nebula/Signals.hh>

#include <Nebula/Actor/Base.hh>
#include <Nebula/Actor/RigidActor/Base.hh>
#include <Nebula/Actor/RigidBody/Base.hh>
#include <Nebula/Actor/Empty/Empty.hpp>
#include <Nebula/Actor/Util/Types.hh>

#include <Nebula/Filter.hh>
#include <Nebula/Graphics/Window/Base.hh>
#include <Nebula/Graphics/Types.hh>

/** @file Base
 */

Neb::Actor::Base::Base() {
}
Neb::Actor::Base::Base(Neb::Actor::Util::Parent_s parent): parent_(parent) {
	NEBULA_ACTOR_BASE_FUNC;
}
Neb::Actor::Base::~Base() {
	NEBULA_ACTOR_BASE_FUNC;
}
void		Neb::Actor::Base::init() {
}
Neb::Actor::Util::Parent_s	Neb::Actor::Base::getParent() {
	return parent_;
}
mat4				Neb::Actor::Base::getPose() {
	return pose_;
}
mat4				Neb::Actor::Base::getPoseGlobal() {
	NEBULA_ACTOR_BASE_FUNC;
	
	mat4 m;

	if(!parent_) {
		m = parent_->getPoseGlobal() * getPose();
	} else {
		m = getPose();
	}

	return m;
}
void		Neb::Actor::Base::setPose(mat4 pose) {
	pose_ = pose;
	
	flag_.set(Neb::Actor::Util::Flag::E::SHOULD_UPDATE);
}
void		Neb::Actor::Base::load_lights(int& i, mat4 space) {
	NEBULA_ACTOR_BASE_FUNC;

	space = space * pose_;
	
	typedef Neb::Actor::Util::Parent A;
	typedef Neb::Shape::Util::Parent S;

	auto lambda_a = [&] (A::map_type::iterator<0> it) {
		
		auto actor = sp::dynamic_pointer_cast<Neb::Actor::Base>(it->ptr_);
		if(!actor) {
			std::cout << "ptr   = " << it->ptr_ << " type= " << typeid(*it->ptr_).name() << std::endl;
			std::cout << "actor = " << actor << std::endl;
			abort();
		}
		actor->load_lights(i, space);
	};

	auto lambda_s = [&]  (S::map_type::iterator<0> it) {
		auto shape = sp::dynamic_pointer_cast<Neb::Shape::Base>(it->ptr_);
		assert(shape);
		shape->load_lights(i, space);
	};
	
	A::map_.for_each<0>(lambda_a);
	
	S::map_.for_each<0>(lambda_s);
}
void		Neb::Actor::Base::draw(Neb::Graphics::Context::Base_s context, mat4 space) {
	NEBULA_ACTOR_BASE_FUNC;

	space = space * pose_;

	typedef Neb::Actor::Util::Parent A;
	typedef Neb::Shape::Util::Parent S;

	A::map_.for_each<0>([&] (A::map_type::iterator<0> it) {
			auto actor = sp::dynamic_pointer_cast<Neb::Actor::Base>(it->ptr_);
			assert(actor);
			actor->draw(context, space);
			});

	S::map_.for_each<0>([&] (S::map_type::iterator<0> it) {
			auto shape = sp::dynamic_pointer_cast<Neb::Shape::Base>(it->ptr_);
			assert(shape);
			shape->draw(context, space);
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

	Neb::Actor::Util::Parent::clear();
	Neb::Shape::Util::Parent::clear();

	//conn_.key_fun_.disconnect();
}
void		Neb::Actor::Base::step(Neb::Core::TimeStep const & ts) {
	NEBULA_ACTOR_BASE_FUNC;

	typedef Neb::Actor::Util::Parent A;
	typedef Neb::Shape::Util::Parent S;

	A::map_.for_each<0>([&] (A::map_type::iterator<0> it) {
			it->ptr_->step(ts);
			});

	S::map_.for_each<0>([&] (S::map_type::iterator<0> it) {
			it->ptr_->step(ts);
			});

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
				_4,
				_5
				).track_foreign(me)
			);

}
int Neb::Actor::Base::key_fun(sp::shared_ptr<Neb::Graphics::Window::Base> window, int key, int scancode, int action, int mods) {

	switch(action) {
		case GLFW_PRESS:
			switch(key) {
				case GLFW_KEY_SPACE:
					//fire();
					return 1;
				case GLFW_KEY_ESCAPE:
					parent_->erase(i_);
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




