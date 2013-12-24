#include <neb/app.h>
#include <neb/view.h>
#include <neb/scene.h>
#include <neb/shape.h>
#include <neb/actor/desc.h>
#include <neb/actor/Base.h>

neb::actor::Base::Base()
{}
int				neb::actor::Base::release() {
	glutpp::actor::release();

	return 0;
}
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
int	neb::actor::Base::fire()
{
	printf("%s\n", __PRETTY_FUNCTION__);

	neb::actor::desc desc = get_projectile();

	assert(!scene_.expired());

	auto scene = get_scene();

	auto me = std::dynamic_pointer_cast<neb::actor::Actor>(shared_from_this());

	auto actor = scene->Create_Rigid_Dynamic(desc, me);

	//auto p = glutpp::__master.use_program(glutpp::program_name::e::LIGHT);

	//actor->init_buffer(p);

	//light
	glutpp::desc_light desc_light;
	desc_light.pos_ = math::vec4(0.0, 0.0, 0.0, 1.0);
	desc_light.atten_linear_ = 2.0;


	scene->Create_Light(desc_light, actor);

	return 1;
}
neb::actor::desc	neb::actor::Base::get_projectile() {
	printf("%s\n", __PRETTY_FUNCTION__);
	exit(0);
	neb::actor::desc desc;
	return desc;
}
void	neb::actor::Base::step_remote(double)
{}
neb::actor::desc	neb::actor::Base::get_desc() {
	
	neb::actor::desc desc = desc_;
	
	desc_.pose.from_math(pose_);
	
	return desc;
}


