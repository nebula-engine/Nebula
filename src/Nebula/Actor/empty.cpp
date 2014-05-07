
#include <nebula/config.hpp>
#include <nebula/actor/empty.hpp>

neb::Actor::empty::empty(glutpp::actor::parent_s parent):
	neb::Actor::Base(parent)
{
	NEBULA_DEBUG_0_FUNCTION;
}
void neb::Actor::empty::init(glutpp::actor::desc_s desc) {
	
	NEBULA_DEBUG_0_FUNCTION;
	
	neb::Actor::Base::init(desc);
}



