
#include <Nebula/config.hh>
#include <Nebula/Actor/empty.hh>

neb::core::actor::empty::empty(sp::shared_ptr<neb::core::actor::Util::Parent> parent):
	neb::core::actor::Base(parent)
{
	//NEBULA_DEBUG_0_FUNCTION;
}
void		neb::core::actor::empty::init() {
	
	//NEBULA_DEBUG_0_FUNCTION;
	
	neb::core::actor::Base::init();
}



