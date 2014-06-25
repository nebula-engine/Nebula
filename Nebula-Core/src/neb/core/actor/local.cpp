#include <neb/core/actor/Local.hh>

neb::core::actor::local::local(sp::shared_ptr<neb::core::actor::util::parent> parent):
	neb::core::actor::base(parent)
{
}
void		neb::core::actor::local::step(gal::std::timestep const & ts) {
	neb::core::actor::base::step(ts);
}

