
//#include <neb/actor/Base.h>
#include <gru/Camera/View/ridealong.hpp>

glutpp::Camera::View::ridealong::ridealong(glutpp::actor::actor_s actor):
	actor_(actor)
{
}
math::mat44<float>	glutpp::Camera::View::ridealong::view()
{
	if(actor_.expired())
	{
		return math::mat44<float>();
	}

	auto actor = actor_.lock();

	if(actor->all(glutpp::actor::actor::flag::SHOULD_RELEASE))
	{
		return math::mat44<float>();
	}



	math::transform<float> pose = actor->get_raw()->pose_;

	math::mat44<float> translate;
	translate.SetTranslation(-pose.p);

	math::mat44<float> rotate(pose.q);

	math::mat44<float> m(pose);
	//pose.Invert();


	// offset vector relative to object
	math::vec3<float> offset_v(0.0,-1.0,-4.0);

	// transform offset vector to object space
	rotate.RotateVector3D(offset_v);

	// create matrix from offset vector
	math::mat44<float> offset_m;
	offset_m.SetTranslation(offset_v);
	
	math::mat44<float> mInv = m.getInverse();
	
	//math::mat44 ret = pose * offset_m;
	math::mat44<float> ret = mInv * offset_m;
	//math::mat44 ret = offset_m * pose.GetInverse();
	//math::mat44 ret = translate;//.GetInverse();

	//ret.SetTranslation(math::vec3(0.0,0.0,-5.0));
	
	std::cout << "inverse" << std::endl;
	mInv.print();

	std::cout << "det(m) = " << m.det() << std::endl;

	std::cout << "view" << std::endl;
	ret.print();
	
	return ret;
}
void glutpp::Camera::View::ridealong::step(double) {
	
}




