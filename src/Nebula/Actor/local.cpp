#include <Nebula/Actor/Local.hh>

neb::core::actor::local::local(sp::shared_ptr<neb::core::actor::util::parent> parent):
	neb::core::actor::base(parent)
{
}
void		neb::core::actor::local::step(neb::core::TimeStep const & ts) {
	neb::core::actor::base::step(ts);
}

