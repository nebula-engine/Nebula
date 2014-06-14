

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

neb::core::actor::base::base() {
}
neb::core::actor::base::base(sp::shared_ptr<neb::core::actor::util::parent> parent): parent_(parent) {
	NEBULA_ACTOR_BASE_FUNC;
}
neb::core::actor::base::~Base() {
	NEBULA_ACTOR_BASE_FUNC;
}
void		neb::core::actor::base::init() {
}
sp::shared_ptr<neb::core::actor::util::parent>	neb::core::actor::base::getParent() {
	return parent_;
}
mat4				neb::core::actor::base::getPose() {
	return pose_;
}
mat4				neb::core::actor::base::getPoseGlobal() {
	NEBULA_ACTOR_BASE_FUNC;
	
	mat4 m;

	if(!parent_) {
		m = parent_->getPoseGlobal() * getPose();
	} else {
		m = getPose();
	}

	return m;
}
void		neb::core::actor::base::setPose(mat4 pose) {
	pose_ = pose;
	
	flag_.set(neb::core::actor::util::Flag::E::SHOULD_UPDATE);
}
void		neb::core::actor::base::load_lights(neb::core::light::util::count & light_count, mat4 space) {
	NEBULA_ACTOR_BASE_FUNC;

	space = space * pose_;
	
	typedef neb::core::actor::util::parent A;
	typedef neb::core::shape::util::parent S;

	auto lambda_actor = [&] (A::map_type::iterator<0> it) {
		
		auto actor = sp::dynamic_pointer_cast<neb::core::actor::base>(it->ptr_);
		if(!actor) {
			::std::cout << "ptr   = " << it->ptr_ << " type= " << typeid(*it->ptr_).name() << ::std::endl;
			::std::cout << "actor = " << actor << ::std::endl;
			abort();
		}
		actor->load_lights(light_count, space);
	};
	
	auto lambda_shape = [&]  (S::map_type::iterator<0> it) {
		auto shape = sp::dynamic_pointer_cast<neb::core::shape::base>(it->ptr_);
		assert(shape);
		shape->load_lights(light_count, space);
	};
	
	A::map_.for_each<0>(lambda_actor);
	
	S::map_.for_each<0>(lambda_shape);
}
void		neb::core::actor::base::draw(sp::shared_ptr<neb::gfx::context::base> context, sp::shared_ptr<neb::glsl::program> p, mat4 space) {
	NEBULA_ACTOR_BASE_FUNC;

	space = space * pose_;

	typedef neb::core::actor::util::parent A;
	typedef neb::core::shape::util::parent S;

	A::map_.for_each<0>([&] (A::map_type::iterator<0> it) {
			auto actor = sp::dynamic_pointer_cast<neb::core::actor::base>(it->ptr_);
			assert(actor);
			actor->draw(context, p, space);
			});

	S::map_.for_each<0>([&] (S::map_type::iterator<0> it) {
			auto shape = sp::dynamic_pointer_cast<neb::core::shape::base>(it->ptr_);
			assert(shape);
			shape->draw(context, p, space);
			});


}
/*void neb::core::actor::base::init(neb::core::actor::desc_w desc) {
  NEBULA_ACTOR_BASE_FUNC;

  raw_.reset();
  raw_.swap(desc->raw_wrapper_.ptr_);


  create_physics();
  create_children(desc);
  create_shapes(desc);
  init_physics();
  }*/
void		neb::core::actor::base::release() {

	neb::core::actor::util::parent::clear();
	neb::core::shape::util::parent::clear();

	//conn_.key_fun_.disconnect();
}
void		neb::core::actor::base::step(neb::core::TimeStep const & ts) {
	NEBULA_ACTOR_BASE_FUNC;

	typedef neb::core::actor::util::parent A;
	typedef neb::core::shape::util::parent S;

	A::map_.for_each<0>([&] (A::map_type::iterator<0> it) {
			it->ptr_->step(ts);
			});

	S::map_.for_each<0>([&] (S::map_type::iterator<0> it) {
			it->ptr_->step(ts);
			});

}
void		neb::core::actor::base::connect(sp::shared_ptr<neb::gfx::window::base> window) {

	//window_ = window;

	//auto me = std::dynamic_pointer_cast<neb::core::actor::base>(shared_from_this());
	auto me = isActorBase();

	//auto shared = sharedBase();

	//conn_.key_fun_.reset(new neb::weak_function<int,int,int,int,int>(&neb::core::actor::base::key_fun));

	assert(window);

	auto c = window->sig_.key_fun_.connect(
			neb::Signals::KeyFun::slot_type(
				&neb::core::actor::base::key_fun,
				me.get(),
				_1,
				_2,
				_3,
				_4,
				_5
				).track_foreign(me)
			);

}
int neb::core::actor::base::key_fun(sp::shared_ptr<neb::gfx::window::base> window, int key, int scancode, int action, int mods) {

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




