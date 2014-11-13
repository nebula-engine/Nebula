
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <gal/log/log.hpp>

#include <neb/core/util/debug.hpp>
//#include <neb/core/input/source.hpp>

#include <neb/gfx/window/Base.hh>
#include <neb/gfx/camera/view/manual.hpp>
#include <neb/gfx/util/log.hpp>

typedef neb::gfx::camera::view::manual THIS;

THIS::manual(std::shared_ptr<neb::gfx::environ::base> parent):
	neb::gfx::camera::view::base(parent),
	eye_(0, 0, 30),
	center_(0, 0, 0),
	up_(0, 1, 0)
{

}
void	THIS::init() {

}


void			THIS::step(gal::etc::timestep const & ts) {
	LOG(lg, neb::gfx::sl, debug) << __PRETTY_FUNCTION__;
}


glm::mat4		THIS::view()
{
	//printf("%s\n", __FUNCTION__);

	glm::mat4 ret = glm::lookAt(eye_, center_, up_);

	return ret;
}






