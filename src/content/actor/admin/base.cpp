#include <nebula/define.hpp>

#include <nebula/content/scene/admin/base.hpp>
#include <nebula/content/actor/physics/base.hpp>
#include <nebula/content/actor/renderer/base.hpp>

#include <nebula/content/actor/admin/base.hpp>

n34100::base::base( jess::shared_ptr<n32100::base> parent ):
	parent_( parent ),
	pose_( physx::PxTransform(physx::PxVec3(0,0,0),physx::PxQuat( 0, physx::PxVec3(0,1,0) ) ) )
{
	jess::clog << NEB_FUNCSIG << std::endl;
	
	//jess::clog << pose_;
	
	NEB_ASSERT( !parent_.expired() )
}
n34100::base::~base()
{
	jess::clog << NEB_FUNCSIG << std::endl;
}
void	n34100::base::init()
{
	jess::clog << NEB_FUNCSIG << std::endl;
}
void	n34100::base::shutdown()
{
	jess::clog << NEB_FUNCSIG << std::endl;
}
void	n34100::base::update()
{
	//mailbox update
}
void	n34100::base::render( jess::shared_ptr<n23000::base> rnd )
{
	jess::clog << NEB_FUNCSIG << std::endl;
}
void	n34100::base::step( float dt )
{
	jess::clog << NEB_FUNCSIG << std::endl;

	physics_->step( dt );
	renderer_->step( dt );
}
void	n34100::base::create_shapes()
{

}
physx::PxMat44	n34100::base::get_pose()
{
	return pose_;
}
void	n34100::base::set_pose( physx::PxMat44 pose )
{
	pose_ = pose;
}
jess::shared_ptr<n34200::material>	n34100::base::create_physics_material()
{
	return parent_.lock()->request_physics_material();
}












