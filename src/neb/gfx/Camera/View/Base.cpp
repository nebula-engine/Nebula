#include <neb/app/Base.hh>
#include <neb/gfx/Camera/View/Base.hh>
#include <neb/gfx/glsl/Uniform/scalar.hpp>

neb::gfx::Camera::View::base::base(sp::shared_ptr<neb::gfx::environ::base> parent):
	parent_(parent)
{
}
void		neb::gfx::Camera::View::base::load(sp::shared_ptr<neb::glsl::program> p) {
	
	p->get_uniform_scalar("view")->load(view());
}


