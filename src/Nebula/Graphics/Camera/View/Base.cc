#include <Nebula/App/Base.hh>
#include <Nebula/Graphics/Camera/View/Base.hh>
#include <Nebula/Graphics/glsl/Uniform/scalar.hpp>

neb::gfx::Camera::View::base::base(sp::shared_ptr<neb::gfx::environ::base> parent):
	parent_(parent)
{
}
void		neb::gfx::Camera::View::base::load(sp::shared_ptr<neb::glsl::program> p) {
	
	p->get_uniform_scalar("view")->load(view());
}


