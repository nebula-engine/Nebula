#include <Nebula/debug.hh>

#include <Nebula/Actor/Actor/Remote.hh>


neb::core::actor::actor::remote::remote(sp::shared_ptr<neb::core::actor::util::parent> parent):
	neb::core::actor::base(parent),
	neb::core::actor::actor::base(parent),
	neb::core::actor::remote(parent)
{

}
void		neb::core::actor::actor::remote::step(neb::core::TimeStep const & ts) {
	//NEBULA_ACTOR_BASE_FUNC;

//	neb::core::actor::actor::base::step(time, dt);
//	neb::core::actor::remote::step(time, dt);
}



