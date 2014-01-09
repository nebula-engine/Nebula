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



glutpp::actor::actor::actor(
		glutpp::actor::desc_shared desc,
		std::shared_ptr<glutpp::scene::scene> scene,
		std::shared_ptr<glutpp::actor::actor> actor)
{	
	printf("%s\n",__PRETTY_FUNCTION__);

	desc_ = desc;
	scene_ = scene;
	actor_ = actor;


	assert(scene);
}

void glutpp::actor::actor::i(int ni) {
	i_ = ni;
}



unsigned int glutpp::actor::actor_base::f() {
	return desc_->raw_.flag_;
}
void glutpp::actor::actor_base::f(unsigned int flag) {
	desc_->raw_.flag_ = flag;
}
void glutpp::actor::actor_base::cleanup() {

	//printf("%s\n",__PRETTY_FUNCTION__);

	auto it = actors_.begin();
	while(it != actors_.end())
	{
		std::shared_ptr<glutpp::actor::actor> actor = it->second;

		actor->cleanup();
		
		if(actor->any(SHOULD_DELETE))
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
		std::shared_ptr<glutpp::shape::shape> shape = s->second;

		shape->cleanup();

		if(shape->any(SHOULD_DELETE))
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
void glutpp::actor::actor_base::release() {

	printf("%s\n",__PRETTY_FUNCTION__);

	assert(!scene_.expired());
	auto scene = scene_.lock();

	for(auto it = actors_.begin(); it != actors_.end(); ++it)
	{
		it->second->release();
	}

	actors_.clear();
}
math::mat44 glutpp::actor::actor_base::get_pose() {

	math::mat44 m(desc_->raw_.pose_.to_math());

	if(!actor_.expired())
	{
		m = actor_.lock()->get_pose() * m;
	}

	return m;
}
void glutpp::actor::actor_base::load_lights(int& i) {

	//printf("%s\n",__PRETTY_FUNCTION__);

	//math::mat44(get_pose()).print();

	for(auto it = actors_.begin(); it != actors_.end(); ++it)
	{
		it->second->load_lights(i);
	}

	for(auto it = shapes_.begin(); it != shapes_.end(); ++it)
	{
		it->second->load_lights(i);
	}

}
std::shared_ptr<glutpp::scene::scene>	glutpp::actor::actor_base::get_scene() {
	assert(!scene_.expired());

	return scene_.lock();
}
void glutpp::actor::actor_base::draw(glutpp::window::window_shared window) {
	
	GLUTPP_DEBUG_1_FUNCTION;
	
	math::mat44 model(desc_->raw_.pose_.to_math());

	for(auto it = shapes_.begin(); it != shapes_.end(); ++it)
	{
		it->second->draw(window, model);
	}
}
/*
void glutpp::actor::actor_base::serialize() {

	auto scene = get_scene();

	std::shared_ptr<gal::network::message> msg(new gal::network::message);
	
	size_t len = desc_->size() + sizeof(int) + sizeof(int);
	
	char data[len];
	char* head = data;
	
	int type = glutpp::network::type::ACTOR_CREATE;
	
	// type
	memcpy(head, &type, sizeof(int));
	head += sizeof(int);
	
	// scene i
	//memcpy(head, &scene->desc_->raw_.i_, sizeof(int));
	
	
	//memcpy(head, &scene->i(), sizeof(int));
	//head += sizeof(int);
	
	// actor desc
	desc_->write(head);
	
	msg->set(data, len);
	
	return msg;
}
*/
void glutpp::actor::actor_base::send_actor_update(std::shared_ptr<glutpp::network::actor::addr_raw_vec> vec) {
	
	assert(vec);
	
	if(any(glutpp::actor::actor::SHOULD_UPDATE))
	{
		vec->vec_.push_back(desc_->raw_);
	}
	
	for(auto it = actors_.begin(); it != actors_.end(); ++it)
	{
		auto actor = it->second;
		
		actor->send_actor_update(vec);
	}
}











