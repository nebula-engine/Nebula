#include <neb/app.h>
#include <neb/view.h>
#include <neb/scene.h>
#include <neb/shape.h>
#include <neb/actor/desc.h>
#include <neb/actor/Base.h>

neb::actor::Base::Base()
{}
std::shared_ptr<neb::app>	neb::actor::Base::get_app()
{
	auto scene = get_scene();

	assert(scene->app_.expired());
	
	return scene->app_.lock();
}
std::shared_ptr<neb::scene>	neb::actor::Base::get_scene()
{
	assert(!scene_.expired());
	
	auto scene = std::dynamic_pointer_cast<neb::scene>(scene_.lock());

	return scene;
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



