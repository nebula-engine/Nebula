#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_inverse.hpp>

#include <gal/log/log.hpp>

#include <neb/core/util/debug.hpp>
#include <neb/core/core/actor/base.hpp>

#include <neb/gfx/util/log.hpp>
#include <neb/gfx/camera/view/ridealong.hh>

neb::gfx::camera::view::ridealong::ridealong(std::shared_ptr<neb::gfx::environ::base> parent, weak_ptr<neb::core::core::actor::base> actor):
	neb::gfx::camera::view::base(parent),
	actor_(actor)
{
}
mat4		neb::gfx::camera::view::ridealong::view() {

	LOG(lg, neb::gfx::sl, debug) << __PRETTY_FUNCTION__;
	
	auto actor = actor_.lock();
	if(!actor) return mat4();

	vec3 translate_vec(actor->pose_.pos_);
	quat rotation(actor->pose_.rot_);


	vec3 offset_vec(0.0,-1.0,-4.0);

	offset_vec = rotation * offset_vec;


	mat4 ret = glm::affineInverse(actor->pose_.mat4_cast());
	
	ret = glm::translate(ret, offset_vec);
	
	return mat4(ret);
}
void neb::gfx::camera::view::ridealong::step(gal::etc::timestep const & ts) {
	
}




