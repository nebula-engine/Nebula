
#include <gal/log/log.hpp>


#include <neb/core/util/debug.hpp>

#include <neb/gfx/app/__gfx_glsl.hpp>

#include <neb/gfx/camera/proj/perspective.hpp>
#include <neb/gfx/camera/view/shadow/point.hpp>

#include <neb/gfx/environ/shadow/point.hpp>
#include <neb/gfx/environ/three.hpp>
#include <neb/gfx/environ/SceneDefault.hpp>
#include <neb/gfx/drawable/base.hpp>
#include <neb/gfx/util/log.hpp>
#include <neb/gfx/glsl/program/base.hpp>
#include <neb/gfx/core/light/directional.hpp>
#include <neb/gfx/camera/proj/base.hpp>
#include <neb/gfx/RenderDesc.hpp>

#include <neb/phx/test.hpp>

neb::gfx::environ::shadow::point::point()
{
}
void		neb::gfx::environ::shadow::point::init() {
	LOG(lg, neb::gfx::sl, debug) << __PRETTY_FUNCTION__;

	auto self = std::dynamic_pointer_cast<neb::gfx::environ::shadow::point>(shared_from_this());

//	auto light = light_.lock();
//	assert(light);

	programs_.d3_.reset(new neb::gfx::glsl::program::base("shadow"));
	programs_.d3_->init();

	programs_.d3_inst_.reset(new neb::gfx::glsl::program::base("shadow_inst"));
	programs_.d3_inst_->init();
	
	static const glm::vec3 look[6] = {
		glm::vec3( 1, 0, 0),
		glm::vec3(-1, 0, 0),
		glm::vec3( 0, 1, 0),
		glm::vec3( 0,-1, 0),
		glm::vec3( 0, 0, 1),
		glm::vec3( 0, 0,-1)
	};
	static const glm::vec3 up[6] = {
		glm::vec3( 0, 1, 0),
		glm::vec3( 0, 1, 0),
		glm::vec3( 0, 0, 1),
		glm::vec3( 0, 0, 1),
		glm::vec3( 1, 0, 0),
		glm::vec3( 1, 0, 0)
	};

	// camera
	
	for(int c = 0; c < 6; c++) {
		view_[c].reset(new neb::gfx::camera::view::shadow::point(self));
		view_[c]->look_ = look[c];
		view_[c]->up_ = up[c];
	}
	
	typedef neb::gfx::camera::proj::perspective pers;
	
	pers* p = new pers(self);

	proj_.reset(p);
	p->set(90.0, 1.0, 100.0);


}
bool		neb::gfx::environ::shadow::point::shouldRender() {
	LOG(lg, neb::gfx::sl, debug) << __PRETTY_FUNCTION__;
	
	assert(programs_.d3_);
	assert(programs_.d3_inst_);

	if(!programs_.d3_->flag_shader_.all(neb::gfx::glsl::program::util::flag_shader::SHADOW)) return false;

	if(!programs_.d3_inst_->flag_shader_.all(neb::gfx::glsl::program::util::flag_shader::SHADOW)) return false;
	
	return true;
}
bool		neb::gfx::environ::shadow::point::shouldRender(unsigned int c) {
	auto e = environ_scene_.lock();
	if(!e) return false;
	
	return query(
			*proj_->_M_px_geometry,
			view_[c]->view(),
			*e->proj_->_M_px_geometry,
			e->view_->view()
			);

}
void		neb::gfx::environ::shadow::point::step(gal::etc::timestep const & ts) {

	LOG(lg, neb::gfx::sl, debug) << __PRETTY_FUNCTION__;

	if(proj_) proj_->step(ts);	
	if(view_) view_[0]->step(ts);	

}
void			neb::gfx::environ::shadow::point::render(
		std::shared_ptr<neb::gfx::context::base> context,
		GLint layer)
{

	LOG(lg, neb::gfx::sl, debug) << __PRETTY_FUNCTION__;

	/**
	 * prepare rendering environment and then call the drawable
	 */

	
	auto drawable = drawable_.lock();

	if(!drawable) {
		LOG(lg, neb::gfx::sl, warning) << "environ has no drawable";
		return;
	}

	//auto self = std::dynamic_pointer_cast<neb::gfx::context::base>(shared_from_this());
	//auto app = neb::gfx::app::__gfx_glsl::global().lock();

	/** wrong for color maybe! */	
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	//glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);

	assert(proj_);
	assert(view_[layer]);

	//program_->use();

//	proj_->load(program_);
//	view_[layer]->load(program_);

	//glViewPort(0, 0, );

	drawable->draw(
			RenderDesc(
				view_[layer].get(),
				proj_.get(),
				programs_.d3_.get(),
				programs_.d3_HF_.get(),
				programs_.d3_inst_.get()
				)
		      );

}		





