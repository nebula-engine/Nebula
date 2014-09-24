
#include <neb/core/math/geo/polyhedron.hh>

#include <neb/gfx/util/config.hpp>
#include <neb/gfx/app/__gfx_glsl.hpp>
#include <neb/gfx/glsl/program/base.hpp>
#include <neb/gfx/mesh/instanced.hpp>

std::weak_ptr<neb::gfx::app::__gfx_glsl>		neb::gfx::app::__gfx_glsl::global()
{
	auto app(std::dynamic_pointer_cast<neb::gfx::app::__gfx_glsl>(g_app_));
	assert(app);
	return app;
}
void		neb::gfx::app::__gfx_glsl::__init() {
}
void		neb::gfx::app::__gfx_glsl::create_programs() {

	printf("%s\n", __PRETTY_FUNCTION__);

	std::shared_ptr<neb::gfx::glsl::program::base> p;

	program_text_.reset(new neb::gfx::glsl::program::base("text"));
	program_text_->init();

	program_tex_.reset(new neb::gfx::glsl::program::base("tex"));
	program_tex_->init();

	program_simple3_.reset(new neb::gfx::glsl::program::base("simple3"));
	program_simple3_->init();

	

}
/*std::shared_ptr<neb::gfx::glsl::program::base>		neb::gfx::app::__gfx_glsl::use_program(neb::program_name::e name){
	auto p = get_program(name);

	p->use();

	current_ = p;

	return p;
}
std::shared_ptr<neb::gfx::glsl::program::base>		neb::gfx::app::__gfx_glsl::current_program(){
	assert(current_);

	return current_;
}*/
/*std::shared_ptr<neb::gfx::glsl::program::base>		neb::gfx::app::__gfx_glsl::get_program(neb::program_name::e name){
	auto it = programs_.find(name);

	if(it == programs_.end())
	{
		printf("program '%i' not found\n", name);
		exit(0);
	}

	auto p = (*it).second;

	assert(p);

	return p;
}*/



