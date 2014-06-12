
#include <Nebula/config.hh>
#include <Nebula/Actor/Empty/Empty.hpp>

neb::core::actor::Empty::Empty(sp::shared_ptr<neb::core::actor::Util::Parent> parent):
	neb::core::actor::Base(parent)
{
	//NEBULA_DEBUG_0_FUNCTION;
}
void		neb::core::actor::Empty::init() {
	
	//NEBULA_DEBUG_0_FUNCTION;
	
	neb::core::actor::Base::init();
}



