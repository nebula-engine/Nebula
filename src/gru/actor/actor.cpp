#include <GL/glew.h>

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <string.h>
#include <png.h>

#include <math/mat44.h>
#include <math/geo/polyhedron.h>

#include <gal/network/vector.h>

#include <glutpp/network/message.h>
#include <glutpp/window/window.h>
#include <glutpp/scene/scene.h>
#include <glutpp/scene/desc.h>
#include <glutpp/actor/actor.h>
#include <glutpp/shape/shape.h>
#include <glutpp/actor/desc.h>
#include <glutpp/actor/raw_factory.h>


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

glutpp::actor::actor::actor(glutpp::parent_s parent): glutpp::parent(parent)
{
	printf("%s\n",__PRETTY_FUNCTION__);

	assert(parent);
}
void glutpp::actor::actor::i(int ni) {
	i_ = ni;
}
int glutpp::actor::actor::i() {
	return i_;
}
glutpp::actor::raw_s glutpp::actor::actor::get_raw()
{
	assert(raw_);
	return raw_;
}
void glutpp::actor::actor::init(glutpp::actor::desc_s desc) {
	int type = desc->get_raw()->type_;

	raw_ = glutpp::master::Global()->get_raw_factory()->create(type);

	assert(raw_);
	//raw_.reset(new glutpp::actor::raw);
	raw_->operator=(*desc->get_raw());
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
	GLUTPP_DEBUG_1_FUNCTION;
	//printf("%s\n",__PRETTY_FUNCTION__);

	auto it = actors_.begin();
	while(it != actors_.end())
	{
		glutpp::actor::actor_s actor = it->second;

		actor->cleanup();

		if(actor->any(glutpp::actor::actor::flag::e::SHOULD_RELEASE))
		{
			actor->release();

			actors_.erase(it);
		}
		else
		{
			++it;
		}
	}

	auto s = shapes_.begin();
	while(s != shapes_.end())
	{
		glutpp::shape::shape_s shape = s->second;

		shape->cleanup();

		if(shape->any(glutpp::shape::flag::e::SHOULD_RELEASE))
		{
			shape->release();

			shapes_.erase(s);
		}
		else
		{
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
math::mat44 glutpp::actor::actor::get_pose() {
	assert(raw_);
	return raw_->pose_;
}
void glutpp::actor::actor::set_pose(math::transform pose) {
	assert(raw_);

	raw_->pose_ = pose;

	set(glutpp::actor::actor::flag::e::SHOULD_UPDATE);

	notify_foundation_change_pose();
}
void glutpp::actor::actor::notify_foundation_change_pose() {

	glutpp::actor::actor_s actor;
	glutpp::shape::shape_s shape;

	for(auto it = actors_.end(); it != actors_.end(); ++it)
	{
		actor = it->second;
		actor->notify_foundation_change_pose();
	}

	for(auto it = shapes_.end(); it != shapes_.end(); ++it)
	{
		shape = it->second;
		shape->notify_foundation_change_pose();
	}
}
void glutpp::actor::actor::load_lights(int& i, math::mat44 space) {
	GLUTPP_DEBUG_1_FUNCTION;
	assert(raw_);

	space *= raw_->pose_;

	for(auto it = actors_.begin(); it != actors_.end(); ++it)
	{
		it->second->load_lights(i, space);
	}

	for(auto it = shapes_.begin(); it != shapes_.end(); ++it)
	{
		it->second->load_lights(i, space);
	}
}
glutpp::scene::scene_s glutpp::actor::actor::get_scene() {
	GLUTPP_DEBUG_1_FUNCTION;

	auto parent = get_parent();
	assert(parent);

	auto scene = std::dynamic_pointer_cast<glutpp::scene::scene>(parent);

	if(scene) return scene;

	auto actor = std::dynamic_pointer_cast<glutpp::actor::actor>(parent);

	if(actor) return actor->get_scene();

	abort();
}
void glutpp::actor::actor::draw(glutpp::window::window_s window, math::mat44 space) {
	GLUTPP_DEBUG_1_FUNCTION;
	assert(raw_);

	space = space * raw_->pose_;

	for(auto it = shapes_.begin(); it != shapes_.end(); ++it)
	{
		it->second->draw(window, space);
	}
}



