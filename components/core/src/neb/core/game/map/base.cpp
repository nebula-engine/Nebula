#include <neb/core/game/map/base.hpp>

<<<<<<< HEAD
neb::game::map::base::base(std::shared_ptr<neb::core::core::scene::util::parent> parent):
	neb::core::core::scene::base(parent)
{}
void		neb::game::map::base::init() {

	neb::core::core::scene::base::init();

	auto spawn(sp::make_shared<neb::game::spawn::base>());

	neb::game::spawn::util::parent::insert(spawn);


=======
neb::game::map::base::base()
{}
void		neb::game::map::base::init(parent_t * const & p)
{

	/** @todo move to createSpawn() */
	auto spawn(std::make_shared<neb::game::spawn::base>());

	neb::game::spawn::util::parent::insert(spawn);

>>>>>>> d0f62233eb8fed722542d3bfcc237575d904a507
}
void		neb::game::map::base::release() {
}

