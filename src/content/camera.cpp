#include <nebula/content/actor/admin/controller.hpp>

#include <nebula/platform/renderer/base.hpp>

#include <nebula/content/camera.hpp>

nebula::content::camera::camera()
{

}
void	nebula::content::camera::render( jess::shared_ptr<nebula::platform::renderer::base> rnd )
{
	jess::clog << NEB_FUNCSIG << std::endl;
	
	physx::PxVec3 e(0,0,0);
	physx::PxVec3 c(0,0,-1);
	physx::PxVec3 u(0,1,0);

	if ( controller_ )
	{
		controller_->look_at( rnd );
	}
	else
	{
		rnd->look_at( e, c, u );
	}

	jess::clog << NEB_FUNCSIG << " exit" << std::endl;
}





