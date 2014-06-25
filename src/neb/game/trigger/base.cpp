#include <neb/game/trigger/base.hpp>

neb::game::trigger::base::base(sp::shared_ptr<neb::game::trigger::util::parent> parent):
	parent_(parent)
{
	assert(parent);
}

