

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_inverse.hpp>

#include <Galaxy-Log/log.hpp>

#include <neb/debug.hh>
#include <neb/core/actor/Base.hh>
#include <neb/gfx/Camera/View/ridealong.hh>

neb::gfx::Camera::View::Ridealong::Ridealong(sp::shared_ptr<neb::gfx::environ::base> parent):
	neb::gfx::Camera::View::base(parent)
{
}
mat4		neb::gfx::Camera::View::Ridealong::view() {

	if(DEBUG_NEB) BOOST_LOG_CHANNEL_SEV(lg, "neb gfx camera view", debug) << __PRETTY_FUNCTION__;
	
	auto actor = actor_.lock();
	if(!actor) return mat4();

	//auto pose = actor_->pose_;
	
	vec3 translate_vec(actor->pose_.pos_);

	//mat4 translate(mat4(-pose.p));
	//translate.SetTranslation(-pose.p);

	quat rotation(actor->pose_.rot_);
	
	//mat4 m(pose);
	//pose.Invert();


	// offset vector relative to object
	vec3 offset_vec(0.0,-1.0,-4.0);

	// transform offset vector to object space
	//rotate.rotate(offset_v);
	offset_vec = rotation * offset_vec;
	
	
	
	// create matrix from offset vector
	//mat4 offset_m = glm::translate(offset_vec);
	//offset_m.SetTranslation(offset_v);
	
	
	mat4 ret = glm::affineInverse(actor->pose_.mat4_cast());
	
	ret = glm::translate(ret, offset_vec);
	
	//math::mat44 ret = pose * offset_m;
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
	return mat4(ret);
}
void neb::gfx::Camera::View::Ridealong::step(gal::std::timestep const & ts) {
	
}




