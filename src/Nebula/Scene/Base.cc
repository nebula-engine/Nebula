#include <stdio.h>

#include <Galaxy-Log/log.hpp>
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
#include <Nebula/Graphics/Light/Util/light_count.hpp>

neb::Scene::Base::Base(sp::shared_ptr<neb::Scene::Util::Parent> parent):
	parent_(parent)
{
	GLUTPP_DEBUG_0_FUNCTION;

	program_name_ = neb::program_name::e::LIGHT;
}
neb::Scene::Base::~Base() {
	GLUTPP_DEBUG_0_FUNCTION;
}
void neb::Scene::Base::init() {
	GLUTPP_DEBUG_0_FUNCTION;
	
}
void neb::Scene::Base::release() {
	GLUTPP_DEBUG_0_FUNCTION;	
}
void neb::Scene::Base::draw(sp::shared_ptr<neb::gfx::Context::Base> context, sp::shared_ptr<neb::glsl::program> p) {

	BOOST_LOG_CHANNEL_SEV(lg, "neb core scene", debug) << __PRETTY_FUNCTION__;

	//auto p = neb::App::Base::globalBase()->use_program(neb::program_name::e::LIGHT);
	
	
	neb::core::light::util::count light_count;
	
	typedef neb::core::actor::Util::Parent A;
	
	A::map_.for_each<0>([&] (A::map_type::iterator<0> it) {
		auto actor = sp::dynamic_pointer_cast<neb::core::actor::Base>(it->ptr_);
		assert(actor);
		actor->load_lights(light_count, mat4());
	});
	
	p->get_uniform_scalar("light_count_point")->load(light_count.point);
	p->get_uniform_scalar("light_count_spot")->load(light_count.spot);
	p->get_uniform_scalar("light_count_directional")->load(light_count.directional);

	//printf("%i\n",i);

	
	A::map_.for_each<0>([&] (A::map_type::iterator<0> it) {
		auto actor = sp::dynamic_pointer_cast<neb::core::actor::Base>(it->ptr_);
		assert(actor);
		actor->draw(context, p, mat4());
	});

}
void					neb::Scene::Base::resize(int w, int h) {
}
mat4					neb::Scene::Base::getPose() {
	return mat4();
}		
mat4					neb::Scene::Base::getPoseGlobal() {
	return mat4();
}
void		neb::Scene::Base::add_deferred(sp::shared_ptr<neb::core::actor::Base> actor) {

	actors_deferred_[actor->name_] = actor;
}
void		neb::Scene::Base::step(neb::core::TimeStep const & ts) {

	typedef neb::core::actor::Util::Parent A;

	A::map_.for_each<0>([&] (A::map_type::iterator<0> it) {
		auto actor = sp::dynamic_pointer_cast<neb::core::actor::Base>(it->ptr_);
		assert(actor);
		actor->step(ts);
	});
	
}







