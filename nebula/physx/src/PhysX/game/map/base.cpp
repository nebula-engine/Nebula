

#include <PhysX/core/scene/util/parent.hpp>
#include <PhysX/game/map/base.hpp>

phx::game::map::base::base(sp::shared_ptr<phx::core::scene::util::parent> parent):
	neb::core::scene::base(parent),
	phx::core::scene::base(parent),
	neb::game::map::base(parent)
{}
void		phx::game::map::base::release() {
}
void		phx::game::map::base::init() {

	phx::core::scene::base::init();
	neb::game::map::base::init();

}

