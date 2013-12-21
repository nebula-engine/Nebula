#include <glutpp/renderable.h>
#include <glutpp/scene.h>

#include <neb/simulation_callback.h>
#include <neb/shape.h>
#include <neb/view.h>
#include <neb/scene.h>
#include <neb/actor/desc.h>
#include <neb/actor/Actor.h>

neb::actor::Actor::Actor():
	px_actor_(NULL)
{}
void	neb::actor::Actor::set_pose(math::transform pose)
{
	pose_ = pose;
}
int	neb::actor::Actor::fire()
{
	printf("%s\n", __PRETTY_FUNCTION__);

	neb::actor::desc desc(neb::actor::RIGID_DYNAMIC);
	
	
	math::vec3 velocity(0.0, 0.0, -2.0);
	velocity = pose_.q.rotate(velocity);
	
	math::vec3 offset(0.0, 0.0, -2.0);
	offset = pose_.q.rotate(offset);
	
	desc.pose_ = pose_;
	desc.pose_.p += offset;

	desc.velocity_ = velocity;
	desc.density_ = 1000.0;
	
	desc.filter_group_ = neb::simulation_callback::filter_group::PROJECTILE;
	desc.filter_mask_ = neb::simulation_callback::filter_group::NORMAL;

	
	neb::shape* shape = new neb::box(math::vec3(0.1,0.1,0.1));
	
	desc.shape_ = shape;
	
	assert(!scene_.expired());
	
	auto scene = get_scene();
	
	auto actor = scene->Create_Rigid_Dynamic(desc);

	auto p = glutpp::__master.use_program(glutpp::program_name::e::LIGHT);
	
	actor->init_buffer(p);
	
	return 1;
}
void	neb::actor::Actor::step_remote(double)
{}

