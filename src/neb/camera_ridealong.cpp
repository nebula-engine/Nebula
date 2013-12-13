#include <neb/actor/Base.h>
#include <neb/camera.h>

neb::camera_ridealong::camera_ridealong():
	actor_(NULL)
{}
math::mat44	neb::camera_ridealong::supply()
{
	if(actor_ == NULL)
	{
		return math::mat44();
	}

	math::mat44 translate;
	translate.SetTranslation(-actor_->pose_.p);
	
	math::mat44 rotate(actor_->pose_.q);
		
	math::mat44 pose(actor_->pose_);
	//pose.Invert();

	
	// offset vector relative to object
	math::vec3 offset_v(0.0,0.0,-3.0);
	
	// transform offset vector to object space
	rotate.RotateVector3D(offset_v);
	
	// create matrix from offset vector
	math::mat44 offset_m;
	offset_m.SetTranslation(offset_v);
	
	
	//math::mat44 ret = pose * offset_m;
	math::mat44 ret = pose.GetInverse() * offset_m;
	//math::mat44 ret = offset_m * pose.GetInverse();
	//math::mat44 ret = translate;//.GetInverse();
	
	//ret.SetTranslation(math::vec3(0.0,0.0,-5.0));
	
	return ret;
}



