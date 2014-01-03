#include <GL/glew.h>

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <string.h>
#include <png.h>

#include <math/mat44.h>
#include <math/geo/polyhedron.h>

#include <glutpp/window.h>
#include <glutpp/scene/scene.h>
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
void	readbuffer(GLuint buffer) {
	GLfloat data[24*4];

	glBindBuffer(GL_ARRAY_BUFFER, buffer);	
	//checkerror("glBindBuffer");

	glGetBufferSubData(GL_ARRAY_BUFFER, 0, 1*4*sizeof(GLfloat), data);
	//checkerror("glGetBufferSubData");
}


glutpp::actor::actor::actor(
		glutpp::actor::desc* desc,
		std::shared_ptr<glutpp::scene> scene,
		std::shared_ptr<glutpp::actor::actor> actor):
	desc_(desc),
	scene_(scene),
	actor_(actor)
{	
	printf("%s\n",__PRETTY_FUNCTION__);

	assert(scene);
}
void glutpp::actor::actor::cleanup() {

	printf("%s\n",__PRETTY_FUNCTION__);

	auto it = actors_.begin();
	while(it != actors_.end())
	{
		std::shared_ptr<glutpp::actor::actor> actor = *it;

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
		std::shared_ptr<glutpp::shape::shape> shape = *s;
	
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

	printf("%s exit\n",__PRETTY_FUNCTION__);
}
void glutpp::actor::actor::release() {

	printf("%s\n",__PRETTY_FUNCTION__);

	assert(!scene_.expired());
	auto scene = scene_.lock();

	for(auto it = actors_.begin(); it != actors_.end(); ++it)
	{
		(*it)->release();
	}
	
	actors_.clear();

	printf("%s exit\n",__PRETTY_FUNCTION__);
}
math::mat44 glutpp::actor::actor::get_pose() {

	math::mat44 m(desc_->raw_.pose_.to_math());

	if(!actor_.expired())
	{
		m = actor_.lock()->get_pose() * m;
	}

	return m;
}
void glutpp::actor::actor::load_lights(int& i) {

	//printf("%s\n",__PRETTY_FUNCTION__);

	//math::mat44(get_pose()).print();

	for(auto it = actors_.begin(); it != actors_.end(); ++it)
	{
		(*it)->load_lights(i);
	}

	for(auto it = shapes_.begin(); it != shapes_.end(); ++it)
	{
		(*it)->load_lights(i);
	}

}
std::shared_ptr<glutpp::scene>	glutpp::actor::actor::get_scene() {
	assert(!scene_.expired());

	return scene_.lock();
}
void glutpp::actor::actor::draw(std::shared_ptr<glutpp::window> window) {

	math::mat44 model(desc_->raw_.pose_.to_math());

	for(auto it = shapes_.begin(); it != shapes_.end(); ++it)
	{
		(*it)->draw(window, model);
	}
}
void	glutpp::shape::vertex::print(){

	printf("% 2.1f % 2.1f % 2.1f % 2.1f % 2.1f % 2.1f % 2.1f % 2.1f % 2.1f\n",
			position.x,position.y,position.z,position.w,
			normal.x,normal.y,normal.z,
			texcoor.x,texcoor.y);
}


