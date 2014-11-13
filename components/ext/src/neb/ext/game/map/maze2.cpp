#include <maze/dfs.hpp>

//#include <neb/core/shape/Box.hh>
//#include <neb/core/actor/RigidStatic/local.hpp>

#include <neb/phx/core/scene/util/parent.hpp>

#include <neb/ext/maze/game/map/maze2.hpp>

neb::ext::maze::game::map::maze2::maze2(
		shared_ptr<neb::fin::gfx_phx::core::scene::util::parent> parent,
		ivec2 size):
	neb::core::core::scene::base(parent),
	neb::game::map::base(parent),
	neb::phx::core::scene::base(parent),
	neb::phx::game::map::base(parent),
	neb::gfx::core::scene::base(parent),
	neb::fin::gfx_phx::core::scene::base(parent),
	size_(size)
{
	
}
void		neb::ext::maze::game::map::maze2::init() {
	
	auto self(std::dynamic_pointer_cast<neb::ext::maze::game::map::maze2>(shared_from_this()));

	// insert a spawn point at origin
	// and init scene
	neb::game::map::base::init();
	neb::fin::gfx_phx::core::scene::base::init();
	
	jess::maze::description2 desc(size_);
	jess::maze::dfs2 m(desc);
	m.run();
	
	double width = 3.0;
	
	auto lambda = [&] (vec2 v) {
		
		neb::core::pose pose;
		pose.pos_ = vec3(v.x,0,v.y);
		
		auto actor = createActorRigidStaticCube(pose, width);
		
		//auto actor = neb::core::actor::util::parent::cii<neb::core::actor::rigidstatic::local, std::shared_ptr<neb::core::scene::local>>(self);
		
		//auto shape = sp::make_shared<neb::core::shape::box>(actor);
		
		//actor->neb::core::shape::util::parent::insert(shape);
		
		//shape->s_ = vec3(width);
		
		//shape->init();
		
		//actor->pose_.pos_ = vec4(v.x,0,v.y,0);
	};

	for(int i = 0; i < desc.size_.x; ++i) {
		for(int j = 0; j < desc.size_.y; ++j) {
			if(!m.get_ispath(ivec2(i,j))) {
				lambda(vec2(i,j) * (float)width);
			}
		}
	}
}
void		neb::ext::maze::game::map::maze2::release() {
}
