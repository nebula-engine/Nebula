#include <neb/config.h>
#include <neb/app.h>
#include <neb/scene/scene.h>
#include <neb/shape.h>
#include <glutpp/actor/desc.h>

#include <neb/actor/Base.h>
#include <neb/actor/empty.h>

neb::actor::Base::Base(
		std::shared_ptr<neb::scene::scene> scene,
		std::shared_ptr<neb::actor::Base> actor):
	glutpp::actor::actor(scene, actor)
{
	NEBULA_DEBUG_0_FUNCTION;
	
	assert(scene);
}
neb::actor::Base::~Base() {
	NEBULA_DEBUG_0_FUNCTION;
}
void neb::actor::Base::init(glutpp::actor::desc_shared desc) {
	NEBULA_DEBUG_0_FUNCTION;

	create_physics();
	create_children(desc);
	create_shapes(desc);
	init_physics();
	
}
void neb::actor::Base::release() {

	glutpp::actor::actor::release();
	
	conn_.key_fun_.reset();
}
void neb::actor::Base::create_children(glutpp::actor::desc_shared desc) {
	NEBULA_DEBUG_0_FUNCTION;

	// create children
	for(auto it = desc->actors_.vec_.begin(); it != desc->actors_.vec_.end(); ++it)
	{
		create_actor(std::get<0>(*it));
	}
	
	
}
neb::actor::Base_shared neb::actor::Base::create_actor(glutpp::actor::desc_shared desc) {
	
	printf("%s\n",__PRETTY_FUNCTION__);
	
	auto scene = get_scene();//std::dynamic_pointer_cast<neb::scene::scene>(shared_from_this());
	
	auto me = std::dynamic_pointer_cast<neb::actor::Base>(shared_from_this());
	
	neb::actor::Base_shared actor;
	
	switch(desc->raw_.type_)
	{
		case glutpp::actor::RIGID_DYNAMIC:
			actor.reset(new neb::actor::Rigid_Dynamic(scene, me));
			// = Create_Rigid_Dynamic(ad);
			break;
		case glutpp::actor::RIGID_STATIC:
			actor.reset(new neb::actor::Rigid_Static(scene, me));
			// = Create_Rigid_Static(ad);
			break;
		case glutpp::actor::PLANE:
			//actor = Create_Rigid_Static_Plane(ad);
			printf("not implemented\n");
			abort();
			break;
		case glutpp::actor::CONTROLLER:
			printf("not implemented\n");
			abort();
			//actor = Create_Controller(ad);
			break;
		case glutpp::actor::EMPTY:
			actor.reset(new neb::actor::empty(scene, me));
			break;
		default:
			abort();
	}
	
	actor->init(desc);
	
	return actor;
}
neb::actor::Base_shared neb::actor::Base::create_actor_local(glutpp::actor::desc_shared desc) {
	auto actor = create_actor(desc);
	actors_.push_back(actor);
	return actor;
}
neb::actor::Base_shared neb::actor::Base::create_actor_remote(
		glutpp::actor::addr_shared addr,
		glutpp::actor::desc_shared desc) {
	auto actor = create_actor(desc);
	abort();
	return actor;
}

std::shared_ptr<neb::app> neb::actor::Base::get_app() {

	auto scene = get_scene();

	assert(!scene->app_.expired());
	
	return scene->app_.lock();
}
std::shared_ptr<neb::scene::scene> neb::actor::Base::get_scene() {

	assert(!scene_.expired());
	
	auto scene = std::dynamic_pointer_cast<neb::scene::scene>(scene_.lock());

	return scene;
}
void	neb::actor::Base::set_pose(math::transform pose) {
	
	raw_.pose_.from_math(pose);
}
int	neb::actor::Base::fire() {

	printf("%s\n", __PRETTY_FUNCTION__);
	
	glutpp::actor::desc_shared desc = get_projectile();
	
	auto scene = get_scene();
	
	auto me = std::dynamic_pointer_cast<neb::actor::Actor>(shared_from_this());
	
	scene->create_actor(desc);
	
	return 1;
}
glutpp::actor::desc_shared neb::actor::Base::get_projectile() {

	NEBULA_DEBUG_0_FUNCTION;
	
	abort();
	
	return glutpp::actor::desc_shared();
}
void	neb::actor::Base::step_remote(double)
{}
glutpp::actor::desc_shared neb::actor::Base::get_desc() {

	NEBULA_DEBUG_0_FUNCTION;
	
	glutpp::actor::desc_shared desc(new glutpp::actor::desc);
	
	desc->raw_ = raw_;
	
	return desc;
}
void neb::actor::Base::create_shapes(glutpp::actor::desc_shared desc)
{
	NEBULA_DEBUG_0_FUNCTION;
	
	auto me = std::dynamic_pointer_cast<neb::actor::Base>(shared_from_this());
	
	std::shared_ptr<neb::shape> shape;

	for(auto it = desc->shapes_.vec_.begin(); it != desc->shapes_.vec_.end(); ++it)
	{
		glutpp::shape::desc_shared sd = std::get<0>(*it);
		
		shape.reset(new neb::shape(me));
		
		shape->init(sd);
		
		shapes_.push_back(shape);
	}
}






