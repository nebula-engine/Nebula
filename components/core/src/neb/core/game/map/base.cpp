#include <neb/core/game/map/base.hpp>

neb::game::map::base::base(std::shared_ptr<neb::core::core::scene::util::parent> parent):
	neb::core::core::scene::base(parent)
{}
void		neb::game::map::base::init() {

	neb::core::core::scene::base::init();

	auto spawn(sp::make_shared<neb::game::spawn::base>());

	neb::game::spawn::util::parent::insert(spawn);


}
void		neb::game::map::base::release() {
}

