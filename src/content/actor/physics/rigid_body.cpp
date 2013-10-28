#include <jess/scoped_ostream.hpp>

#include <nebula/content/actor/physics/rigid_body.hpp>


n34200::rigid_body::rigid_body( std::shared_ptr<n34100::base> parent ):
	actor( parent ),
	rigid_actor( parent )
{

}
n34200::rigid_body::~rigid_body()
{

}
void	n34200::rigid_body::init()
{
	n34200::rigid_actor::init();
	
	// density and velocity
	velocity_ = physx::PxVec3(0,0,0);

	density_ = 1000;

	jess::assertion( px_actor_ );

	physx::PxRigidBody* px_rigid_body = (::physx::PxRigidBody*)px_actor_;

	physx::PxRigidBodyExt::updateMassAndInertia( *px_rigid_body, density_ );

	px_rigid_body->setLinearVelocity( velocity_ );
}
void	n34200::rigid_body::shutdown()
{

}
void	n34200::rigid_body::update()
{

}
void	n34200::rigid_body::step( float dt )
{
	jess::scoped_ostream( &jess::cout, NEB_FUNCSIG );
}
void	n34200::rigid_body::render( std::shared_ptr<n23000::base> rnd )
{

}






