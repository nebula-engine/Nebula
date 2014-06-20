
#include <Nebula/config.hh>
#include <Nebula/core/actor/Empty/Empty.hpp>

neb::core::actor::Empty::Empty(sp::shared_ptr<neb::core::actor::util::parent> parent):
	neb::core::actor::base(parent)
{
	//NEBULA_DEBUG_0_FUNCTION;
}
void		neb::core::actor::Empty::init() {
	
	//NEBULA_DEBUG_0_FUNCTION;
	
	neb::core::actor::base::init();
}



