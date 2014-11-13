
#include <neb/core/game/game/base.hpp>

void		neb::game::game::base::init(parent_t * const & p)
{
}
void		neb::game::game::base::release()
{
}
void		neb::game::game::base::step(gal::etc::timestep const & ts)
{
	neb::game::ai::util::parent::step(ts);
	neb::game::trigger::util::parent::step(ts);
}

