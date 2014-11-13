

#include <neb/phx/core/scene/util/parent.hpp>
#include <neb/phx/game/map/base.hpp>

neb::phx::game::map::base::base(std::shared_ptr<neb::phx::core::scene::util::parent> parent):
	neb::core::core::scene::base(parent),
	neb::phx::core::scene::base(parent),
	neb::game::map::base(parent)
{}
void		neb::phx::game::map::base::release() {
}
void		neb::phx::game::map::base::init() {

	neb::phx::core::scene::base::init();
	neb::game::map::base::init();

}

