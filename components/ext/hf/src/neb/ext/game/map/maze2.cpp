
//#include <neb/core/shape/Box.hh>
//#include <neb/core/actor/RigidStatic/local.hpp>

#include <neb/core/core/actor/base.hpp>
#include <neb/core/core/shape/HeightField/desc.hpp>
#include <neb/phx/core/scene/util/parent.hpp>


#include <neb/ext/maze/game/map/maze2.hpp>

typedef neb::fin::gfx_phx::core::scene::base	T0;
typedef neb::ext::maze::game::map::base		T1;

extern "C" T0*	scene_create()
{
	std::cout << __PRETTY_FUNCTION__ << std::endl;
	return new T1;
}
extern "C" void	scene_destroy(T0* t)
{
	std::cout << __PRETTY_FUNCTION__ << std::endl;
	delete t;
}

neb::ext::maze::game::map::base::base():
	init_hf_(false)
{
		std::cout << __PRETTY_FUNCTION__ << std::endl;
}

#define D 3

void		neb::ext::maze::game::map::base::init(parent_t * const & p)
{
	
	std::cout << __PRETTY_FUNCTION__ << std::endl;
	
	auto self(std::dynamic_pointer_cast<neb::ext::maze::game::map::base>(shared_from_this()));
	
	// init scene
	neb::game::map::base::init(p);
	neb::fin::gfx_phx::core::scene::base::init(p);


	// insert a spawn point at origin
	// ?

	// create heightfield

	if(!init_hf_)
	{
		auto actor = createActorRigidStaticUninitialized().lock();
		actor->pose_.pos_ = glm::vec3(0,0,0);
		actor->init(this);

		neb::core::core::shape::HeightField::desc d;
		d.w = 50.0;
		d.h = 50.0;
		d.r = 128;
		d.c = 128;
		d.hs = 10.0;
		d.fc.push_back(0.2);
		d.fc.push_back(0.2);
		
		actor->createShapeHeightField(d);

		// light
		createActorLightPoint(glm::vec3(
					0.0 * d.w / 2.0,
					0.0,
					0.0 * d.h / 2.0));
/*		createActorLightPoint(glm::vec3(
					d.w / 2.0,
					8.0,
					d.h / 2.0));*/
/*		createActorLightPoint(glm::vec3(
					d.w / 2.0,
					-50.0,
					d.h / 2.0));
*/
		init_hf_ = true;
	}
}
void		neb::ext::maze::game::map::base::release()
{
	std::cout << __PRETTY_FUNCTION__ << std::endl;

	neb::game::map::base::release();
	neb::fin::gfx_phx::core::scene::base::release();
}
void		neb::ext::maze::game::map::base::step(gal::etc::timestep const & ts)
{
	//std::cout << __PRETTY_FUNCTION__ << std::endl;

	//neb::game::map::base::step(ts);
	//neb::phx::game::map::base::step(ts);
	neb::fin::gfx_phx::core::scene::base::step(ts);

}



