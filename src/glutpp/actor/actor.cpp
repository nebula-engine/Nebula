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












