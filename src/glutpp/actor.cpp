#include <GL/glew.h>

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <string.h>
#include <png.h>

#include <math/mat44.h>
#include <math/geo/polyhedron.h>

#include <glutpp/window.h>
#include <glutpp/scene.h>
#include <glutpp/actor.h>
#include <glutpp/shape.h>


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




glutpp::actor::actor() {

	printf("%s\n",__PRETTY_FUNCTION__);
}
int	glutpp::actor::release() {

	printf("%s\n",__PRETTY_FUNCTION__);
	
	assert(!scene_.expired());
	auto scene = scene_.lock();
	
	for(auto a = actors_.begin(); a != actors_.end(); ++a)
	{
		scene->remove_actor(*a);
	}
	
	for(auto b = lights_.begin(); b != lights_.end(); ++b)
	{
		scene->remove_light(*b);
	}
	
	actors_.clear();
	lights_.clear();
}
/*void	glutpp::actor::init(std::shared_ptr<scene> scene) {

	printf("%s\n",__PRETTY_FUNCTION__);
	
	assert(scene);
	
	scene_ = scene;
}*/
std::shared_ptr<glutpp::scene>	glutpp::actor::get_scene() {
	assert(!scene_.expired());
	
	return scene_.lock();
}
int	glutpp::actor::draw(std::shared_ptr<glutpp::window> window) {
	
	math::mat44 model(pose_);
	
	for(auto s = shapes_.begin(); s != shapes_.end(); ++s)
	{
		(*s)->draw(window, model);
	}	
}
void	glutpp::vertex::print(){

	printf("% 2.1f % 2.1f % 2.1f % 2.1f % 2.1f % 2.1f % 2.1f % 2.1f % 2.1f\n",
			position.x,position.y,position.z,position.w,
			normal.x,normal.y,normal.z,
			texcoor.x,texcoor.y);
	//position.print();
	//normal.print();
	//texcoor.print();
}


