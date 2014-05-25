#include <Nebula/App/Base.hh>
#include <Nebula/Graphics/Camera/View/Base.hh>

Neb::Graphics::Camera::View::Base::Base(Neb::Graphics::Context::Base_s parent): parent_(parent) {
}
void		Neb::Graphics::Camera::View::Base::load() {
	auto p = Neb::App::Base::globalBase()->get_program(Neb::program_name::e::LIGHT);

	p->get_uniform_scalar("view")->load(view());
}


