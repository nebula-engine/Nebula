
#include <PhysX/core/actor/actor/remote.hpp>

phx::core::actor::actor::remote::remote(sp::shared_ptr<phx::core::actor::util::parent> parent):
	neb::core::actor::base(parent),
	neb::core::actor::actor::base(parent),
	neb::core::actor::remote(parent),
	neb::core::actor::actor::remote(parent),
	phx::core::actor::base(parent),
	phx::core::actor::remote(parent),
	phx::core::actor::actor::base(parent)
{}
void		phx::core::actor::actor::remote::init() {
	
	neb::core::actor::actor::remote::init();
	phx::core::actor::actor::base::init();
	
}
/*void		phx::core::actor::actor::remote::release() {

	neb::core::actor::actor::remote::release();
	phx::core::actor::actor::base::release();

}*/
void		phx::core::actor::actor::remote::step(gal::std::timestep const & ts) {
	
	neb::core::actor::actor::remote::step(ts);
	phx::core::actor::actor::base::step(ts);


}


