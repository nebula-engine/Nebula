#include <maze/dfs.hpp>

//#include <neb/core/shape/Box.hh>
//#include <neb/core/actor/RigidStatic/local.hpp>
#include <neb/ext/maze/game/map/maze2.hpp>

neb::ext::maze::game::map::maze2::maze2(
		sp::shared_ptr<neb::core::scene::util::parent> parent,
		ivec2 size):
	neb::core::scene::base(parent),
	neb::game::map::base(parent),
	size_(size)
{
	
}
void		neb::ext::maze::game::map::maze2::init() {
	
	auto self(sp::dynamic_pointer_cast<neb::ext::maze::game::map::maze2>(shared_from_this()));

	// insert a spawn point at origin
	// and init scene
	neb::game::map::base::init();
	
	
	jess::maze::description2 desc(size_);
	jess::maze::dfs2 m(desc);
	m.run();
	
	real width = 3.0;
	
	auto lambda = [&] (vec2 v) {
		
		neb::core::pose pose;
		pose.pos_ = vec4(v.x,0,v.y,0);
		
		auto actor = createActorRigidStaticCube(pose, width);
		
		//auto actor = neb::core::actor::util::parent::cii<neb::core::actor::rigidstatic::local, sp::shared_ptr<neb::core::scene::local>>(self);
		
		//auto shape = sp::make_shared<neb::core::shape::box>(actor);
		
		//actor->neb::core::shape::util::parent::insert(shape);
		
		//shape->s_ = vec3(width);
		
		//shape->init();
		
		//actor->pose_.pos_ = vec4(v.x,0,v.y,0);
	};

	for(int i = 0; i < desc.size_.x; ++i) {
		for(int j = 0; j < desc.size_.y; ++j) {
			if(!m.get_ispath(ivec2(i,j))) {
				lambda(width * vec2(i,j));
			}
		}
	}
}

