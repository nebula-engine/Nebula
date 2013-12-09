#include <neb/actor/Base.h>

neb::actor::Base::Base():
	pose_(math::transform( math::vec3(0.0f, 0.0f, 0.0f), math::quat( 0.0f, math::vec3(1.0f, 0.0f, 0.0f) ) ) ),
	list_(0)
{

}
