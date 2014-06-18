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

	real width = 1.0;

	auto lambda = [&] (vec2 v) {
		auto actor = scene->cii<neb::core::actor::rigidstatic::local, sp::shared_ptr<neb::core::scene::local>>(scene);
		
		auto shape = sp::make_shared<neb::core::shape::Box>(actor);
		
		actor->neb::core::shape::util::parent::insert(shape);
		
		shape->s_ = vec3(width);
		
		shape->init();
		
		actor->pose_.pos_ = vec3(v.x,v.y,0);
	};

	for(int i = 0; i < desc.size_.x; ++i) {
		for(int j = 0; j < desc.size_.y; ++j) {
			if(!m.get_ispath(ivec2(i,j))) {
				lambda(width * vec2(i,j));
			}
		}
	}
}

