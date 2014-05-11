#include <Nebula/Graphics/Camera/View/Base.hpp>

/** @brief Load view matrix into GLSL. */
void		Neb::Camera::View::Base::load() {
	auto p = Neb::App::global()->get_program(Neb::program_name::e::LIGHT);

	p->get_uniform_scalar("view")->load(view());
}
