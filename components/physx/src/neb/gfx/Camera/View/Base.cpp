//#include <neb/app/base.hpp>
#include <neb/gfx/free.hpp>
#include <neb/gfx/camera/view/Base.hh>
#include <neb/gfx/glsl/program/base.hpp>
#include <neb/gfx/glsl/uniform/scalar.hpp>

neb::gfx::camera::view::base::base(std::shared_ptr<neb::gfx::environ::base> parent):
	parent_(parent)
{
}
void		neb::gfx::camera::view::base::load(neb::gfx::glsl::program::base const * const p) {
	
	assert(p);

	auto v = view();

	glUniformMatrix4fv(
			p->uniform_table_[neb::gfx::glsl::uniforms::VIEW],
			1,
			GL_FALSE,
			&v[0][0]);

	checkerror("glUniformMatrix4fv");
}


