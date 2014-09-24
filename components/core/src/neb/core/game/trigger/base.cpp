#include <neb/core/game/trigger/base.hpp>

neb::game::trigger::base::base(std::shared_ptr<neb::game::trigger::util::parent> parent):
	parent_(parent)
{
	assert(parent);
}

