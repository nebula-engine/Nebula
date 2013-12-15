#include <neb/shape.h>
#include <neb/actor/Rigid_Dynamic.h>

neb::actor::Rigid_Dynamic::Rigid_Dynamic()
{}
void	neb::actor::Rigid_Dynamic::init()
{
	printf("%s\n",__PRETTY_FUNCTION__);

	assert(shape_);

	object_.reset(new glutpp::object);
	object_->s_ = shape_->s_;

	switch(shape_->type_)
	{
		case neb::shape::BOX:
			object_->load("cube.obj");
			break;
		case neb::shape::SPHERE:
			object_->load("sphere.obj");
			break;
		default:
			break;
	}
}

