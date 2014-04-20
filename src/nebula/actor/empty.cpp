
#include <nebula/config.hpp>
#include <nebula/actor/empty.hpp>

neb::actor::empty::empty(glutpp::parent_s parent):
	neb::actor::Base(parent)
{
	NEBULA_DEBUG_0_FUNCTION;
}
void neb::actor::empty::init(glutpp::actor::desc_s desc) {
	
	NEBULA_DEBUG_0_FUNCTION;
	
	neb::actor::Base::init(desc);
}



