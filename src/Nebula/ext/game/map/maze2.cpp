#include <maze/dfs.hpp>

#include <Nebula/ext/maze/game/map/maze2.hpp>

neb::ext::maze::game::map::maze2::maze2(
		sp::shared_ptr<neb::core::scene::util::parent> parent,
		ivec2 size):
	neb::core::scene::base(parent),
	neb::game::map::base(parent),
	size_(size)
{
	
}
void		neb::ext::maze::game::map::maze2::init() {
	
	neb::game::map::base::init();
	

	jess::maze::description2 desc(size_);
	jess::maze::dfs2 m(desc);
	m.run();
	
	
	
}

