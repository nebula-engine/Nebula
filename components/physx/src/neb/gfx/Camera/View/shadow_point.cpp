#include <neb/gfx/environ/shadow/point.hpp>
#include <neb/gfx/environ/vis_depth.hpp>
#include <neb/gfx/camera/view/shadow/point.hpp>
#include <neb/gfx/core/light/point.hpp>

neb::gfx::camera::view::shadow::point::point(std::shared_ptr<neb::gfx::environ::base> parent):
	neb::gfx::camera::view::base(parent)
{
	assert(parent);


	//light_ = light;

}
glm::mat4				neb::gfx::camera::view::shadow::point::view() {

	auto parent = parent_.lock();
	assert(parent);

	std::shared_ptr<neb::gfx::core::light::point> light;

	auto p2 = std::dynamic_pointer_cast<neb::gfx::environ::shadow::point>(parent);
	auto p3 = std::dynamic_pointer_cast<neb::gfx::environ::vis_depth>(parent);
	if(p2) {
		light = p2->light_.lock();
		assert(light);
	} else if(p3) {
		light = std::dynamic_pointer_cast<neb::gfx::core::light::point>(p3->light_.lock());
		assert(light);
	}

	assert(light);
	
	glm::vec3 eye = light->getPoseGlobal().pos_;
	
	return glm::lookAt(eye, eye + look_, up_);

}
void					neb::gfx::camera::view::shadow::point::step(gal::etc::timestep const & ts) {
}




