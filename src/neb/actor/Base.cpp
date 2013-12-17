#include <neb/app.h>
#include <neb/view.h>
#include <neb/scene.h>
#include <neb/shape.h>
#include <neb/actor/desc.h>
#include <neb/actor/Base.h>

neb::actor::Base::Base():
	pose_(math::transform(
				math::vec3(0.0f, 0.0f, 0.0f), math::quat( 0.0f, math::vec3(1.0f, 0.0f, 0.0f))
			     ))
{}
std::shared_ptr<neb::app>	neb::actor::Base::get_app()
{
	assert(!scene_.expired());
	assert(!scene_.lock()->app_.expired());
	
	return scene_.lock()->app_.lock();
}
void	neb::actor::Base::set_pose(math::transform pose)
{
	pose_ = pose;
}
int	neb::actor::Base::fire(int,int,int)
{
	return 1;
}
void	neb::actor::Base::step_remote(double)
{}



