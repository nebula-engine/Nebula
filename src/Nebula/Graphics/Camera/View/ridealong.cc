#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_inverse.hpp>

#include <Nebula/Actor/Base.hh>
#include <Nebula/Graphics/Camera/View/ridealong.hh>

neb::gfx::Camera::View::Ridealong::Ridealong(sp::shared_ptr<neb::gfx::Context::Base> parent):
	neb::gfx::Camera::View::Base(parent)
{
}
mat4		neb::gfx::Camera::View::Ridealong::view() {

	if(!actor_) return mat4();

	mat4 pose = actor_->pose_;
	
	//vec3 translate_vec(pose[13], pose[14], pose[15]);
	vec3 translate_vec(pose[3][0], pose[3][1], pose[3][2]);

	//mat4 translate(mat4(-pose.p));
	//translate.SetTranslation(-pose.p);

	mat3 rotation(pose);//(pose.q);
	
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
	
	mat4 poseInv = glm::affineInverse(pose);

	glm::translate(poseInv, offset_vec);
	
	//math::mat44 ret = pose * offset_m;
	mat4 ret = poseInv;
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
void neb::gfx::Camera::View::Ridealong::step(neb::core::TimeStep const & ts) {
	
}




