#include <neb/shape.h>
#include <neb/actor/Rigid_Static.h>

void	neb::actor::Rigid_Static::init()
{
	printf("%s\n",__PRETTY_FUNCTION__);

	assert(shape_);

	object_ = new glutpp::object;
	object_->pose_ = pose_;
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
void	neb::actor::Rigid_Static::add_force()
{

}

