
#include <Nebula/core/scene/Base.hh>

#include <Nebula/debug.hh>
#include <Nebula/util/typedef.hpp>
#include <Nebula/core/shape/Base.hh>

#include <Nebula/core/actor/Actor/Base.hh>

//neb::core::actor::actor::base::base() {
//}
neb::core::actor::actor::base::base(sp::shared_ptr<neb::core::actor::util::parent> parent):
	neb::core::actor::base(parent)
{
	NEBULA_ACTOR_BASE_FUNC;
}
void		neb::core::actor::actor::base::init() {
	NEBULA_ACTOR_BASE_FUNC;

	neb::core::actor::base::init();
}
void		neb::core::actor::actor::base::setPose(neb::core::pose const & pose) {
	NEBULA_ACTOR_BASE_FUNC;

	neb::core::actor::base::setPose(pose);
}
void		neb::core::actor::actor::base::step(gal::std::timestep const & ts) {
	neb::core::actor::base::step(ts);
}
/*void		neb::core::actor::actor::base::release() {
	NEBULA_ACTOR_BASE_FUNC;
	
	neb::core::actor::base::release();

}*/



