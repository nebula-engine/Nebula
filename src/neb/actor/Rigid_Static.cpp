#include <neb/shape.h>
#include <neb/actor/Rigid_Static.h>

void	neb::actor::Rigid_Static::init()
{
	printf("%s\n",__PRETTY_FUNCTION__);
/*
	//object_.reset(new glutpp::object);

	s_ = shape_.s.to_math();
	
	switch(shape_.type)
	{
		case neb::shape::BOX:
			load("cube.obj");
			break;
		case neb::shape::SPHERE:
			load("sphere.obj");
			break;
		default:
			break;
	}
*/
}
void	neb::actor::Rigid_Static::add_force()
{

}

