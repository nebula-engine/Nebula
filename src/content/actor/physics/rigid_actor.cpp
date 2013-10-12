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

	materials_.push( parent_.lock()->create_physics_material() );

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
jess::shared_ptr<n35200::box>		n34200::rigid_actor::create_box()
{
	jess::clog << NEB_FUNCSIG << std::endl;
	
	jess::shared_ptr<n35200::box> box( new n35200::box() );
	
	// PxRigidActor
	physx::PxRigidActor* px_rigid_actor = (physx::PxRigidActor*)px_actor_;
	
	// physics material
	jess::shared_ptr<n34200::material> mat = materials_.at(0);
	jess::assertion( bool( mat ) );
	
	// PxMaterial
	::physx::PxMaterial* px_mat = mat->px_material_;
	jess::assertion( bool( px_mat ) );
		
	// PxBoxGeometry
	::physx::PxBoxGeometry px_geometry(1,1,1);
	
	// PxShape
	box->px_shape_ = px_rigid_actor->createShape( px_geometry, *px_mat );
	jess::assertion( bool( box->px_shape_ ) );

	return box;
}



