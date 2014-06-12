#include <Nebula/App/Base.hh>
#include <Nebula/Graphics/Camera/View/Base.hh>
#include <Nebula/Graphics/glsl/Uniform/scalar.hpp>

neb::gfx::Camera::View::Base::Base(sp::shared_ptr<neb::gfx::Context::Base> parent): parent_(parent) {
}
void		neb::gfx::Camera::View::Base::load(sp::shared_ptr<neb::glsl::program> p) {
	
	p->get_uniform_scalar("view")->load(view());
}


