
#include <PhysX/core/scene/util/parent.hpp>

#include <PhysX/ext/maze/game/map/maze2.hpp>

phx::ext::maze::game::map::maze2::maze2(
		sp::shared_ptr<phx::core::scene::util::parent> parent,
		ivec2 size):
	neb::core::scene::base(parent),
	neb::core::scene::local(parent),
	neb::game::map::base(parent),
	neb::ext::maze::game::map::maze2(parent, size),
	phx::core::scene::base(parent),
	phx::core::scene::local(parent),
	phx::game::map::base(parent)
{
	
}
void		phx::ext::maze::game::map::maze2::init() {
	
	phx::game::map::base::init();
	neb::ext::maze::game::map::maze2::init();

}

