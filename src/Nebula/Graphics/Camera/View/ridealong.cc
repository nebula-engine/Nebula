
#include <Nebula/Actor/Base.hh>
#include <Nebula/Graphics/Camera/View/ridealong.hh>

Neb::Graphics::Camera::View::Ridealong::Ridealong(Neb::Graphics::Context::Base_s parent):
	Neb::Graphics::Camera::View::Base(parent)
{
}
physx::PxMat44	Neb::Graphics::Camera::View::Ridealong::view() {
	auto actor = actor_.lock();

	if(!actor) return physx::PxMat44();

	physx::PxTransform pose = actor->pose_;

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
void Neb::Graphics::Camera::View::Ridealong::step(double) {
	
}




