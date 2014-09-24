#include <neb/core/game/map/base.hpp>

neb::game::map::base::base()
{}
void		neb::game::map::base::init(parent_t * const & p)
{

	/** @todo move to createSpawn() */
	auto spawn(std::make_shared<neb::game::spawn::base>());

	neb::game::spawn::util::parent::insert(spawn);

}
void		neb::game::map::base::release() {
}

