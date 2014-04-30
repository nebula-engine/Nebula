#include <GL/glew.h>

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <string.h>
#include <png.h>

//#include <math/mat44.hpp>
//#include <math/geo/polyhedron.hpp>

//#include <galaxy/network/vector.hpp>

#include <gru/debug.hpp>
#include <gru/network/message.hpp>
#include <gru/window/window.hpp>
#include <gru/scene/scene.hpp>
#include <gru/scene/desc.hpp>
#include <gru/actor/actor.hpp>
#include <gru/shape/shape.hpp>
#include <gru/actor/desc.hpp>
#include <gru/actor/raw_factory.hpp>

#define VALUE_TO_STRING(x) #x
#define VALUE(x) VALUE_TO_STRING(x)

//#pragma message VALUE(__cplusplus)
/*
void	print_vector(GLfloat* v, unsigned int m, unsigned int n) {
	for(unsigned int a=0;a<m;++a)
	{
		for(unsigned int b = 0; b < n; ++b)
		{
			printf("% .2f ",v[(a*n)+b]);
		}
		printf("\n");
	}

}
void	print_vectori(GLushort* v, unsigned int m, unsigned int n) {

	for(unsigned int a = 0; a < m; ++a)
	{
		for(unsigned int b = 0; b < n; ++b)
		{
			printf("% 3i ",v[(a*n)+b]);
		}
		printf("\n");
	}

}
*/
glutpp::actor::actor::actor(boost::shared_ptr<glutpp::actor::parent> parent):
	parent_(parent)
{
	GRU_ACTOR_ACTOR_FUNC
	
	assert(parent);
}
void glutpp::actor::actor::i(int ni) {
	i_ = ni;
}
int glutpp::actor::actor::i() {
	return i_;
}
boost::shared_ptr<glutpp::actor::parent>	glutpp::actor::actor::getParent() {
	assert(!parent_.expired());
	return parent_.lock();
}
void glutpp::actor::actor::init(glutpp::actor::desc_s desc) {
	/*
	glutpp::actor::Type type = desc->raw_->type_;
	
	glutpp::master::Global()->get_raw_factory()->reset(raw_, type);
	
	assert(raw_);
	//raw_.reset(new glutpp::actor::raw);
	raw_->operator=(*desc->get_raw());*/
	
	// instead of allocating a new raw and copying it, just swap the one in the desc object, it shouldn't be used for anything else... swap it!!!
	raw_.reset();
	raw_.swap(desc->raw_);
}
unsigned int glutpp::actor::actor::f() {
	assert(raw_);
	return raw_->flag_;
}
void glutpp::actor::actor::f(unsigned int flag) {
	assert(raw_);
	raw_->flag_ = flag;
}
void glutpp::actor::actor::cleanup() {
	GRU_ACTOR_ACTOR_FUNC;
	//printf("%s\n",__PRETTY_FUNCTION__);
	
	auto it = actors_.begin();
	while(it != actors_.end()) {
		boost::shared_ptr<glutpp::actor::actor> actor = it->second;
		
		actor->cleanup();
		
		if(actor->any(glutpp::actor::actor::flag::e::SHOULD_RELEASE)) {
			actor->release();
			it = actors_.erase(it);
		} else {
			++it;
		}
	}

	auto s = shapes_.begin();
	while(s != shapes_.end()) {
		boost::shared_ptr<glutpp::shape::shape> shape = s->second;

		shape->cleanup();

		if(shape->any(glutpp::shape::flag::e::SHOULD_RELEASE)) {
			shape->release();
			shapes_.erase(s);
		} else {
			++s;
		}
	}
}
void glutpp::actor::actor::release() {
	printf("%s\n",__PRETTY_FUNCTION__);

	for(auto it = actors_.begin(); it != actors_.end(); ++it)
	{
		it->second->release();
	}

	actors_.clear();
}
void glutpp::actor::actor::step(double time) {

	shapes_.foreach<glutpp::shape::shape>(std::bind(
				&glutpp::shape::shape::step,
				std::placeholders::_1,
				time));

}
physx::PxMat44		glutpp::actor::actor::getPose() {
	assert(raw_);
	return raw_->pose_;
}
physx::PxMat44 glutpp::actor::actor::getPoseGlobal() {
	GRU_ACTOR_ACTOR_FUNC;

	physx::PxMat44 m;
	
	if(!parent_.expired()) {
		m = parent_.lock()->getPoseGlobal() * getPose();
	} else {
		m = getPose();
	}

	return m;
}
void		glutpp::actor::actor::set_pose(physx::PxTransform pose) {
	assert(raw_);

	raw_->pose_ = pose;

	set(glutpp::actor::actor::flag::e::SHOULD_UPDATE);

	notify_foundation_change_pose();
}
void glutpp::actor::actor::notify_foundation_change_pose() {

	boost::shared_ptr<glutpp::actor::actor> actor;
	boost::shared_ptr<glutpp::shape::shape> shape;


	for(auto it = actors_.end(); it != actors_.end(); ++it) {
		actor = it->second;
		actor->notify_foundation_change_pose();
	}

	for(auto it = shapes_.end(); it != shapes_.end(); ++it) {
		shape = it->second;
		shape->notify_foundation_change_pose();
	}
}
void		glutpp::actor::actor::load_lights(int& i, physx::PxMat44 space) {
	GRU_ACTOR_ACTOR_FUNC;
	assert(raw_);

	space = space * physx::PxMat44(raw_->pose_);

	for(auto it = actors_.begin(); it != actors_.end(); ++it)
	{
		it->second->load_lights(i, space);
	}

	for(auto it = shapes_.begin(); it != shapes_.end(); ++it)
	{
		it->second->load_lights(i, space);
	}
}
boost::shared_ptr<glutpp::scene::scene>		glutpp::actor::actor::get_scene() {
	GRU_ACTOR_ACTOR_FUNC;

	auto parent = getParent();
	assert(parent);

	auto scene = parent->isScene(); //boost::dynamic_pointer_cast<glutpp::scene::scene>(parent);

	if(scene) return scene;

	auto actor = boost::dynamic_pointer_cast<glutpp::actor::actor>(parent);

	if(actor) return actor->get_scene();

	abort();
}
void		glutpp::actor::actor::draw(glutpp::window::window_s window, physx::PxMat44 space) {
	GRU_ACTOR_ACTOR_FUNC;
	assert(raw_);

	space = space * raw_->pose_;

	for(auto it = shapes_.begin(); it != shapes_.end(); ++it)
	{
		it->second->draw(window, space);
	}
}



