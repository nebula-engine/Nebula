#include <nebula/platform/renderer/base.hpp>

#include <nebula/content/shape/physics/box.hpp>

n35200::box::box()
{

}
n35200::box::~box()
{

}
void	n35200::box::init( jess::shared_ptr<n35100::base> parent )
{
	n35200::base::init( parent );

	create_shape();
}
void	n35200::box::shutdown()
{
	
}
void	n35200::box::create_shape()
{
	jess::clog << NEB_FUNCSIG << std::endl;

/*	
	// admin rigid_actor
	jess::shared_ptr<n34100::rigid_actor> ad_act = parent_.lock()->parent_.lock();

	// physics rigid_actor
	jess::shared_ptr<n34200::rigid_actor> ph_act = std::dynamic_pointer_cast<n34200::rigid_actor>( ad_act->physics_ );
	
	// physx rigid_actor
	jess::shared_ptr<n34200p::rigid_actor> ph_px_act = std::dynamic_pointer_cast<n34200::physx::rigid_actor>( ph_act );
	
	// Pxrigid_actor
	::physx::PxRigidActor* px_rigid_actor = (::physx::PxRigidActor*)( ph_px_act->px_actor_ );
	
	// physx material
	jess::shared_ptr<n34200p::material> mat = std::dynamic_pointer_cast<n34200p::material>( ad_act->materials_.at(0)->physics_ );
	//jess::assertion( bool(mat) ); //throw jess::except("no material");
	
	// PxMaterial
	::physx::PxMaterial* px_mat = mat->px_material_;
	jess::assertion( bool(px_mat) ); //throw jess::except("no material");
	
	// PxBoxGeometry
	::physx::PxBoxGeometry px_geometry( 1, 1, 1 );
	
	// PxShape
	px_shape_ = px_rigid_actor->createShape( px_geometry, *px_mat );
	jess::assertion( bool(px_shape_) );  //throw jess::except("m_pxShape");
*/
}




