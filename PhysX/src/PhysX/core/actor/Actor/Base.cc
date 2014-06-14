
#include <Nebula/Graphics/Context/Base.hh>
#include <Nebula/Scene/Base.hh>

#include <Nebula/debug.hh>
#include <Nebula/Util/typedef.hpp>
//#include <Nebula/simulation_callback.hh>
#include <Nebula/Shape/Base.hh>

#include <Nebula/Actor/Actor/Base.hh>

neb::core::actor::actor::base::base() {
}
neb::core::actor::actor::base::base(sp::shared_ptr<neb::core::actor::util::parent> parent):
	neb::core::actor::base(parent)
{
	NEBULA_ACTOR_BASE_FUNC;
}
void		neb::core::actor::actor::base::init() {
	NEBULA_ACTOR_BASE_FUNC;

	neb::core::actor::base::init();
}
void		neb::core::actor::actor::base::set_pose(mat4 pose) {
	NEBULA_ACTOR_BASE_FUNC;

	neb::core::actor::base::setPose(pose);
}
int		neb::core::actor::actor::base::fire() {
	NEBULA_ACTOR_BASE_FUNC;
	return neb::core::actor::base::fire();
}
void		neb::core::actor::actor::base::step(neb::core::TimeStep const & ts) {
}


void		neb::core::actor::actor::base::release() {
	NEBULA_ACTOR_BASE_FUNC;
	
	neb::core::actor::base::release();

	//assert(!scene_.expired());

}



