#include <math/mat44.h>

#include <glutpp/parent.h>

glutpp::parent::parent(glutpp::parent_s parent):
	parent_(parent)
{
	GLUTPP_DEBUG_1_FUNCTION;
}
glutpp::parent::~parent() {
	GLUTPP_DEBUG_1_FUNCTION;
}
glutpp::parent_s glutpp::parent::get_parent() {
	GLUTPP_DEBUG_1_FUNCTION;

	if(!parent_.expired())
	{
		return parent_.lock();
	}

	return  glutpp::parent_s();
}
math::mat44 glutpp::parent::get_pose_global() {
	GLUTPP_DEBUG_1_FUNCTION;

	math::mat44 m;

	if(!parent_.expired())
	{
		m = parent_.lock()->get_pose_global() * get_pose();
	}
	else
	{
		m = get_pose();
	}

	return m;
}



