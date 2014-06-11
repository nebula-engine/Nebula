#include <stdio.h>

#include <Galaxy-Network/message.hpp>

#include <Nebula/Graphics/Window/Base.hh>
#include <Nebula/Graphics/Context/Base.hh>


#include <Nebula/Scene/Base.hh>
#include <Nebula/Scene/Util/Types.hh>
#include <Nebula/Scene/Util/Parent.hh>

#include <Nebula/Actor/Base.hh>

#include <Nebula/Graphics/Light/Base.hh>
#include <Nebula/Graphics/glsl/program.hh>
#include <Nebula/Graphics/Camera/Projection/Perspective.hh>

//#include <math/free.hpp>

#include <Nebula/Actor/Util/Type.hh>
#include <Nebula/Message/Actor/Event/Base.hh>
#include <Nebula/Message/Actor/Create.hh>
#include <Nebula/Message/Actor/Update.hh>
#include <Nebula/Message/Actor/Event/Base.hh>
//#include <Nebula/Util/Typed.hh>
#include <Nebula/Memory/smart_ptr.hh>

#include <Nebula/config.hh> // nebula/config.hpp.in
#include <Nebula/App/Base.hh>
//#include <Nebula/actor/free.hh>
#include <Nebula/Actor/RigidDynamic/Base.hh>
#include <Nebula/Actor/RigidStatic/Base.hh>
#include <Nebula/Actor/Controller/Base.hh>
//#include <Nebula/actor/vehicle.hh>
#include <Nebula/Actor/Empty/Empty.hpp>
#include <Nebula/Shape/Base.hh>
#include <Nebula/timer/Types.hh>
#include <Nebula/timer/Actor/Release.hpp>
#include <Nebula/Graphics/glsl/Uniform/scalar.hpp>

Neb::Scene::Base::Base(Neb::Scene::Util::Parent_s parent):
	parent_(parent)
{
	GLUTPP_DEBUG_0_FUNCTION;
}
Neb::Scene::Base::~Base() {
	GLUTPP_DEBUG_0_FUNCTION;
}
void Neb::Scene::Base::init() {
	GLUTPP_DEBUG_0_FUNCTION;
	
}
void Neb::Scene::Base::release() {
	GLUTPP_DEBUG_0_FUNCTION;	
}
void Neb::Scene::Base::draw(sp::shared_ptr<Neb::Graphics::Context::Base> context) {
	
	GLUTPP_DEBUG_0_FUNCTION;

	//auto p = Neb::App::Base::globalBase()->use_program(Neb::program_name::e::LIGHT);
	auto p = Neb::App::Base::globalBase()->current_program();
	
	
	
	int i = 0;
	
	typedef Neb::Actor::Util::Parent A;
	
	A::map_.for_each<0>([&] (A::map_type::iterator<0> it) {
		auto actor = sp::dynamic_pointer_cast<Neb::Actor::Base>(it->ptr_);
		assert(actor);
		actor->load_lights(i, mat4());
	});

	p->get_uniform_scalar("light_count")->load(i);

	//printf("%i\n",i);

	
	A::map_.for_each<0>([&] (A::map_type::iterator<0> it) {
		auto actor = sp::dynamic_pointer_cast<Neb::Actor::Base>(it->ptr_);
		assert(actor);
		actor->draw(context, mat4());
	});

}
void					Neb::Scene::Base::resize(int w, int h) {
}
mat4					Neb::Scene::Base::getPose() {
	return mat4();
}		
mat4					Neb::Scene::Base::getPoseGlobal() {
	return mat4();
}
void		Neb::Scene::Base::add_deferred(Neb::Actor::Base_s actor) {

	actors_deferred_[actor->name_] = actor;
}
void		Neb::Scene::Base::step(Neb::Core::TimeStep const & ts) {

	typedef Neb::Actor::Util::Parent A;

	A::map_.for_each<0>([&] (A::map_type::iterator<0> it) {
		auto actor = sp::dynamic_pointer_cast<Neb::Actor::Base>(it->ptr_);
		assert(actor);
		actor->step(ts);
	});
	
}







