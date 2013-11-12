
#include <assert.h>

#include <GRU/Window.h>

#include <NEB/Scene.h>
#include <NEB/View.h>

NEB::View::View():
	scene_( NULL ),
	pitch_(0),
	yaw_(0)
{

}
void	NEB::View::SetWindow( GRU::Window* window )
{
	assert( window );

	window->CallBackDisplay_ = std::bind( &NEB::View::Display, this );
	window->CallBackIdle_ = std::bind( &NEB::View::Display, this );
}
void	NEB::View::Display()
{

	if( scene_ )
	{
		scene_->Display();
	}

	Look();
}
void NEB::View::Look()
{
	physx::PxVec3 eye(0.0f,0.0f, 5.0f);
	physx::PxVec3 up(0,1,0);
	physx::PxVec3 look(0,0,-1);


	physx::PxQuat rot( yaw_, physx::PxVec3(0,1,0) );

	rot *= physx::PxQuat( pitch_ , physx::PxVec3(1,0,0) );


	up = rot.rotate( up );
	look = rot.rotate( look );

	physx::PxVec3 center = eye + look;



	gluLookAt(
			eye.x, eye.y, eye.z,
			center.x, center.y, center.z,
			up.x, up.y, up.z );

}
void NEB::View::FirstOrderDeltaPitch(float d)
{
	pitch_ += d;
}
void NEB::View::FirstOrderDeltaYaw(float d)
{
	yaw_ += d;
}






