
#include <Nebula/config.hpp>
#include <Nebula/Actor/empty.hpp>

Neb::Actor::empty::empty(Neb::Actor::parent_w parent):
	Neb::Actor::Base(parent)
{
	//NEBULA_DEBUG_0_FUNCTION;
}
void		Neb::Actor::empty::init(Neb::Actor::desc_w desc) {
	
	//NEBULA_DEBUG_0_FUNCTION;
	
	Neb::Actor::Base::init(desc);
}



