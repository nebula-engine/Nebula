
#include <Nebula/Graphics/Context/Base.hh>
#include <Nebula/Scene/Base.hh>

#include <Nebula/debug.hh>
#include <Nebula/Util/typedef.hpp>
//#include <Nebula/simulation_callback.hh>
#include <Nebula/Shape/Base.hh>

#include <PhysX/core/actor/util/parent.hpp>
#include <PhysX/core/actor/actor/base.hpp>

//neb::core::actor::actor::base::base() {
//}
phx::core::actor::actor::base::base(sp::shared_ptr<phx::core::actor::util::parent> parent):
	neb::core::actor::base(parent),
	neb::core::actor::actor::base(parent),
	phx::core::actor::base(parent)
{
	//NEBULA_ACTOR_BASE_FUNC;
}
void		phx::core::actor::actor::base::init() {
	//NEBULA_ACTOR_BASE_FUNC;

	phx::core::actor::base::init();
}
void		phx::core::actor::actor::base::set_pose(mat4 pose) {
	//NEBULA_ACTOR_BASE_FUNC;

	phx::core::actor::base::setPose(pose);
}
int		phx::core::actor::actor::base::fire() {
	//NEBULA_ACTOR_BASE_FUNC;
	return phx::core::actor::base::fire();
}
void		phx::core::actor::actor::base::step(neb::core::TimeStep const & ts) {
}


void		phx::core::actor::actor::base::release() {
	NEBULA_ACTOR_BASE_FUNC;
	
	neb::core::actor::base::release();

	//assert(!scene_.expired());

}



