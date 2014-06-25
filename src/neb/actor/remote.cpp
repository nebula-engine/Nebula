

#include <neb/core/actor/Remote.hh>

neb::core::actor::remote::remote(sp::shared_ptr<neb::core::actor::util::parent> parent):
	neb::core::actor::base(parent)
{
}
void		neb::core::actor::remote::step(gal::std::timestep const & ts) {
	neb::core::actor::base::step(ts);
}

