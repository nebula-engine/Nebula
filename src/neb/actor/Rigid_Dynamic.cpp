#include <neb/shape.h>
#include <neb/actor/Rigid_Dynamic.h>

neb::actor::Rigid_Dynamic::Rigid_Dynamic()
{}
void	neb::actor::Rigid_Dynamic::init()
{
	printf("%s\n",__PRETTY_FUNCTION__);

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
}

