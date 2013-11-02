#include <nebula/define.hpp>

#include <nebula/utilities/free.hpp>

#include <nebula/platform/renderer/base.hpp>
#include <nebula/platform/key.hpp>
#include <nebula/platform/window/base.hpp>

#include <nebula/content/actor/physics/controller.hpp>
#include <nebula/content/actor/renderer/controller.hpp>
#include <nebula/content/actor/control/controller/def.hpp>


#include <nebula/content/actor/admin/controller.hpp>

n34100::controller::base::base( std::shared_ptr<n32100::base> parent ):
	n34100::base( parent )
{
	jess::clog << NEB_FUNCSIG << std::endl;
}
n34100::controller::base::~base()
{
	jess::clog << NEB_FUNCSIG << std::endl;
}
void	n34100::controller::base::init()
{
	jess::clog << NEB_FUNCSIG << std::endl;

	NEB_ASSERT( bool( physics_ ) );

	// parent
	n34100::base::init();

	flag_ = 0;

	yaw_ = 0;
	pitch_ = 0;

	pos_ = physx::PxVec3(0,0,2);

	std::shared_ptr<n34100::controller::base> this_ptr = std::dynamic_pointer_cast<n34100::controller::base>( shared_from_this() );

	// control
	control_.reset( new n34400::controller::def( this_ptr ) );
	control_->init();

	// renderer
	renderer_.reset( new n34300::controller( shared_from_this() ) );
	renderer_->init();	
}
void	n34100::controller::base::shutdown()
{
	jess::clog << NEB_FUNCSIG << std::endl;
}
void	n34100::controller::base::update()
{
	n34100::base::update();
}
void	n34100::controller::base::step( float dt )
{
	n34100::base::step( dt );
}
void	n34100::controller::base::render( std::shared_ptr<n23000::base> rnd )
{
}
void	n34100::controller::base::create_shapes()
{

}
void	n34100::controller::base::look_at( std::shared_ptr<n23000::base> rnd )
{
	jess::clog << NEB_FUNCSIG << std::endl;
	
	std::shared_ptr<n34200::controller> physics = std::dynamic_pointer_cast<n34200::controller>( physics_ );
	
	
	
	physx::PxQuat rot( yaw_, physx::PxVec3(0,1,0) );

	rot *= physx::PxQuat( pitch_ , physx::PxVec3(1,0,0) );

	up_ = physx::PxVec3(0,1,0);
	look_ = physx::PxVec3(0,0,-1);

	up_ = rot.rotate( up_ );
	look_ = rot.rotate( look_ );

	/** \todo
	 * create set of functions throughout content for updating data after a physx simulate
	 */
	physx::PxExtendedVec3 pos = physics->px_controller_->getPosition();
	pos_ = physx::toVec3( pos );
	
	rnd->look_at( pos_, pos_ + look_, up_ );
}
/*
   void	n34100::controller::base::process_event( int evnt )
   {
   switch ( evnt )
   {
   case event::eRESET_VIEW_ANGLES:
   printf("reset viewing angles\n");
   yaw_ = 0;
   pitch_ = 0;
   break;
   }
   }
 */


