
#include <neb/core/game/weapon/base.hpp>

neb::game::weapon::base::base():
	last_(0),
	cooldown_(1.0)
{}
void		neb::game::weapon::base::init(parent_t * const & p)
{
}

