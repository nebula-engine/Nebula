#include <stdio.h>

#include <Galaxy-Log/log.hpp>
#include <Galaxy-Network/message.hpp>

//#include <neb/gfx/window/Base.hh>
//#include <neb/gfx/Context/Base.hh>

#include <neb/debug.hh>
#include <neb/core/scene/Base.hh>
#include <neb/core/scene/Util/Types.hh>
#include <neb/core/scene/Util/Parent.hh>

#include <neb/core/actor/base.hpp>

#include <neb/core/light/base.hpp>
//#include <neb/core/light/spot.hpp>
#include <neb/gfx/glsl/program.hh>
#include <neb/gfx/Camera/Projection/Perspective.hh>


#include <neb/core/actor/Util/Type.hh>

#include <neb/config.hh> // nebula/config.hpp.in
#include <neb/app/Base.hh>
//#include <neb/actor/free.hh>
#include <neb/core/shape/base.hpp>
#include <neb/timer/Types.hh>
#include <neb/timer/Actor/Release.hpp>
#include <neb/gfx/glsl/Uniform/scalar.hpp>
#include <neb/core/light/util/light_count.hpp>

neb::gfx::core::scene::base::base(sp::shared_ptr<neb::core::scene::util::parent> parent):
	parent_(parent)
{
	if(DEBUG_NEB) BOOST_LOG_CHANNEL_SEV(lg, "neb core scene", debug) << __PRETTY_FUNCTION__;
}
neb::gfx::core::scene::base::~base() {
	if(DEBUG_NEB) BOOST_LOG_CHANNEL_SEV(lg, "neb core scene", debug) << __PRETTY_FUNCTION__;
}
void			neb::gfx::core::scene::base::init() {
	if(DEBUG_NEB) BOOST_LOG_CHANNEL_SEV(lg, "neb core scene", debug) << __PRETTY_FUNCTION__;
}
void			neb::gfx::core::scene::base::release() {
	if(DEBUG_NEB) BOOST_LOG_CHANNEL_SEV(lg, "neb core scene", debug) << __PRETTY_FUNCTION__;
	
	neb::core::scene::base::release();
}
void			neb::gfx::core::scene::base::draw(sp::shared_ptr<neb::gfx::context::base> context, sp::shared_ptr<neb::glsl::program> p) {

	if(DEBUG_NEB) BOOST_LOG_CHANNEL_SEV(lg, "neb core scene", debug) << __PRETTY_FUNCTION__;

	//auto p = neb::app::base::globalBase()->use_program(neb::program_name::e::LIGHT);


	neb::core::light::util::count light_count;

	typedef neb::core::actor::util::parent A;

	A::map_.for_each<0>([&] (A::map_type::iterator<0> it) {
			auto actor = sp::dynamic_pointer_cast<neb::core::actor::base>(it->ptr_);
			assert(actor);
			actor->load_lights(light_count, neb::core::pose());
			});

	p->get_uniform_scalar("light_count_point")->load(light_count.point);
	p->get_uniform_scalar("light_count_spot")->load(light_count.spot);
	p->get_uniform_scalar("light_count_directional")->load(light_count.directional);

	//printf("%i\n",i);


	A::map_.for_each<0>([&] (A::map_type::iterator<0> it) {
			auto actor = sp::dynamic_pointer_cast<neb::core::actor::base>(it->ptr_);
			assert(actor);
			actor->draw(context, p, neb::core::pose());
			});

}
void						neb::gfx::core::scene::base::resize(int w, int h) {
}
void						neb::gfx::core::scene::base::step(gal::std::timestep const & ts) {
}




