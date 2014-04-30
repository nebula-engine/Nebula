
//#include <neb/actor/Base.h>
#include <gru/Camera/View/ridealong.hpp>

glutpp::Camera::View::ridealong::ridealong(glutpp::actor::actor_s actor):
	actor_(actor)
{
}
physx::PxMat44	glutpp::Camera::View::ridealong::view()
{
	if(actor_.expired())
	{
		return physx::PxMat44();
	}

	auto actor = actor_.lock();

	if(actor->all(glutpp::actor::actor::flag::SHOULD_RELEASE))
	{
		return physx::PxMat44();
	}



	physx::PxTransform pose = actor->raw_->pose_;

	physx::PxMat44 translate(physx::PxTransform(-pose.p));
	//translate.SetTranslation(-pose.p);

	physx::PxMat44 rotate(pose.q);

	//physx::PxMat44 m(pose);
	//pose.Invert();


	// offset vector relative to object
	physx::PxVec3 offset_v(0.0,-1.0,-4.0);

	// transform offset vector to object space
	rotate.rotate(offset_v);

	// create matrix from offset vector
	physx::PxTransform offset_m(offset_v);
	//offset_m.SetTranslation(offset_v);
	
	physx::PxTransform poseInv = pose.getInverse();
	
	//math::mat44 ret = pose * offset_m;
	physx::PxTransform ret = poseInv * offset_m;
	//math::mat44 ret = offset_m * pose.GetInverse();
	//math::mat44 ret = translate;//.GetInverse();

	//ret.SetTranslation(math::vec3(0.0,0.0,-5.0));
	
	/*
	std::cout << "inverse" << std::endl;
	//mInv.print();

	std::cout << "det(m) = " << m.det() << std::endl;

	std::cout << "view" << std::endl;
	//ret.print();
	*/
	return physx::PxMat44(ret);
}
void glutpp::Camera::View::ridealong::step(double) {
	
}




