#include <Nebula/debug.hh>

#include <Nebula/core/actor/Actor/Local.hh>

neb::core::actor::actor::local::local(sp::shared_ptr<neb::core::actor::util::parent> parent):
	neb::core::actor::base(parent),
	neb::core::actor::actor::base(parent),
	neb::core::actor::local(parent)
{

}
void		neb::core::actor::actor::local::step(gal::std::timestep const & ts) {
	NEBULA_ACTOR_BASE_FUNC;

	//	neb::core::actor::actor::base::step(dt);
	//	neb::core::actor::local::step(dt);
}

