#include <jess/ostream.hpp>

#include <nebula/define.hpp>
#include <nebula/content/shape/physics/base.hpp>
#include <nebula/content/shape/renderer/base.hpp>

#include <nebula/content/shape/admin/base.hpp>

nebula::content::shape::admin::base::base( jess::shared_ptr<n34100::rigid_actor> parent ):
	parent_( parent ),
	pose_( physx::PxTransform() ),
	scale_( physx::PxVec3(1,1,1) )
{
	jess::clog << NEB_FUNCSIG << std::endl;
}
nebula::content::shape::admin::base::~base()
{
	jess::clog << NEB_FUNCSIG << std::endl;
}
void	nebula::content::shape::admin::base::init()
{
	jess::clog << NEB_FUNCSIG << std::endl;
}
void	nebula::content::shape::admin::base::shutdown()
{
	jess::clog << NEB_FUNCSIG << std::endl;
}
void	nebula::content::shape::admin::base::render( jess::shared_ptr<n23000::base> rnd )
{
	jess::clog << NEB_FUNCSIG << std::endl;

	renderer_->render( rnd );
}
physx::PxVec3	n35100::base::get_scale()
{
	jess::clog << NEB_FUNCSIG << std::endl;

	return scale_;
}




