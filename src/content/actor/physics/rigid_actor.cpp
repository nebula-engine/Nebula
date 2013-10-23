#include <nebula/content/actor/admin/rigid_actor.hpp>
#include <nebula/content/actor/physics/material.hpp>
#include <nebula/content/shape/physics/box.hpp>

#include <nebula/content/actor/physics/rigid_actor.hpp>

n34200::rigid_actor::rigid_actor( jess::shared_ptr<n34100::base> parent ):
actor( parent )
{
}
n34200::rigid_actor::~rigid_actor()
{
}
void	n34200::rigid_actor::init()
{
	n34200::actor::init();

	material_ = parent_.lock()->create_physics_material();

}
void	n34200::rigid_actor::shutdown()
{
	
}
void	n34200::rigid_actor::update()
{
	
}
void	n34200::rigid_actor::step(float dt)
{
	
}
void	n34200::rigid_actor::render( jess::shared_ptr<n23000::base> rnd )
{

}
void	n34200::rigid_actor::create_shapes()
{

}

