#include <neb/actor/desc.h>

neb::actor::desc::desc(neb::actor::type t):
	type_(t),
	density_(1000.0),
	filter_group_(0),
	filter_mask_(0)
{}

