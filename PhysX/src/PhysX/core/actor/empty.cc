
#include <Nebula/config.hh>
#include <Nebula/Actor/empty.hh>

neb::Actor::empty::empty(sp::shared_ptr<neb::Actor::Util::Parent> parent):
	neb::Actor::Base(parent)
{
	//NEBULA_DEBUG_0_FUNCTION;
}
void		neb::Actor::empty::init() {
	
	//NEBULA_DEBUG_0_FUNCTION;
	
	neb::Actor::Base::init();
}



