#include <neb/core/game/trigger/base.hpp>

<<<<<<< HEAD
neb::game::trigger::base::base(std::shared_ptr<neb::game::trigger::util::parent> parent):
	parent_(parent)
{
	assert(parent);
=======
neb::game::trigger::base::base()
{
}
void	neb::game::trigger::base::step(gal::etc::timestep const &)
{
>>>>>>> d0f62233eb8fed722542d3bfcc237575d904a507
}

