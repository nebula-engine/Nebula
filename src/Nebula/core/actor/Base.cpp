#include <gal/log/log.hpp>

#include <Nebula/debug.hh>

//#include <Nebula/util/Typed.hh>

#include <Nebula/util/decl.hpp>
#include <Nebula/config.hh> // Nebula/config.hpp.in
#include <Nebula/timer/Actor/Base.hpp>
//#include <Nebula/app/Base.hh>
#include <Nebula/core/scene/Base.hh>
#include <Nebula/gfx/window/util/signals.hpp>

#include <Nebula/core/actor/Base.hh>
#include <Nebula/core/actor/RigidActor/Base.hh>
#include <Nebula/core/actor/RigidBody/Base.hh>
#include <Nebula/core/actor/Empty/Empty.hpp>
#include <Nebula/core/actor/Util/Types.hh>

#include <Nebula/gfx/window/Base.hh>
#include <Nebula/gfx/util/decl.hpp>

/** @file Base
 */

//neb::core::actor::base::base() {
//}
neb::core::actor::base::base(sp::shared_ptr<neb::core::actor::util::parent> parent):
	density_(10.0),
	parent_(parent)
{
	if(DEBUG_NEB) BOOST_LOG_CHANNEL_SEV(lg, "neb core actor", debug) << __PRETTY_FUNCTION__;
}
neb::core::actor::base::~base() {
	if(DEBUG_NEB) BOOST_LOG_CHANNEL_SEV(lg, "neb core actor", debug) << __PRETTY_FUNCTION__;
}
void		neb::core::actor::base::init() {
}
sp::shared_ptr<neb::core::actor::util::parent>	neb::core::actor::base::get_parent() {
	auto parent(parent_.lock());
	assert(parent);
	return parent;
}
neb::core::pose				neb::core::actor::base::getPose() {
	return pose_;
}
neb::core::pose				neb::core::actor::base::getPoseGlobal() {
	if(DEBUG_NEB) BOOST_LOG_CHANNEL_SEV(lg, "neb core actor", debug) << __PRETTY_FUNCTION__;
	
	neb::core::pose p;
	
	auto parent(parent_.lock());
	
	if(!parent) {
		p = parent->getPoseGlobal() * getPose();
	} else {
		p = getPose();
	}

	return p;
}
void		neb::core::actor::base::setPose(neb::core::pose const & pose) {
	pose_ = pose;
	
	flag_.set(neb::core::actor::util::flag::E::SHOULD_UPDATE);
}
void		neb::core::actor::base::load_lights(neb::core::light::util::count & light_count, neb::core::pose const & pose) {
	if(DEBUG_NEB) BOOST_LOG_CHANNEL_SEV(lg, "neb core actor", debug) << __PRETTY_FUNCTION__;

	auto npose = pose * pose_;
	
	typedef neb::core::actor::util::parent A;
	typedef neb::core::shape::util::parent S;

	auto lambda_actor = [&] (A::map_type::iterator<0> it) {
		
		auto actor = sp::dynamic_pointer_cast<neb::core::actor::base>(it->ptr_);
		if(!actor) {
			::std::cout << "ptr   = " << it->ptr_ << " type= " << typeid(*it->ptr_).name() << ::std::endl;
			::std::cout << "actor = " << actor << ::std::endl;
			abort();
		}
		actor->load_lights(light_count, npose);
	};
	
	auto lambda_shape = [&]  (S::map_type::iterator<0> it) {
		auto shape = sp::dynamic_pointer_cast<neb::core::shape::base>(it->ptr_);
		assert(shape);
		shape->load_lights(light_count, npose);
	};
	
	A::map_.for_each<0>(lambda_actor);
	
	S::map_.for_each<0>(lambda_shape);
}
void			neb::core::actor::base::draw(sp::shared_ptr<neb::gfx::context::base> context, sp::shared_ptr<neb::glsl::program> p,
		neb::core::pose const & pose) {
	if(DEBUG_NEB) BOOST_LOG_CHANNEL_SEV(lg, "neb core actor", debug) << __PRETTY_FUNCTION__;

	auto npose = pose * pose_;

	typedef neb::core::actor::util::parent A;
	typedef neb::core::shape::util::parent S;

	A::map_.for_each<0>([&] (A::map_type::iterator<0> it) {
			auto actor = sp::dynamic_pointer_cast<neb::core::actor::base>(it->ptr_);
			assert(actor);
			actor->draw(context, p, npose);
			});

	S::map_.for_each<0>([&] (S::map_type::iterator<0> it) {
			auto shape = sp::dynamic_pointer_cast<neb::core::shape::base>(it->ptr_);
			assert(shape);
			shape->draw(context, p, npose);
			});


}
/*void neb::core::actor::base::init(neb::core::actor::desc_w desc) {
  if(DEBUG_NEB) BOOST_LOG_CHANNEL_SEV(lg, "neb core actor", debug) << __PRETTY_FUNCTION__;

  raw_.reset();
  raw_.swap(desc->raw_wrapper_.ptr_);


  create_physics();
  create_children(desc);
  create_shapes(desc);
  init_physics();
  }*/
void		neb::core::actor::base::releaseUp() {
	
	gal::std::__release::release();
	
	neb::core::actor::util::parent::clear();
	neb::core::shape::util::parent::clear();

	//conn_.key_fun_.disconnect();
}
void		neb::core::actor::base::step(gal::std::timestep const & ts) {
	if(DEBUG_NEB) BOOST_LOG_CHANNEL_SEV(lg, "neb core actor", debug) << __PRETTY_FUNCTION__;

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
					get_parent()->erase(i_);
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




