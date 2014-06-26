#include <stdio.h>
#include <assert.h>

#include <gal/log/log.hpp>

#include <neb/debug.hh>
#include <neb/app/Base.hh>
#include <neb/util/decl.hpp>
#include <neb/gfx/core/light/base.hpp>
#include <neb/gfx/window/Base.hh>
#include <neb/core/scene/Base.hh>
#include <neb/core/shape/base.hpp>
#include <neb/free.hh>
#include <neb/gfx/glsl/Uniform/vector.hpp>


neb::gfx::core::light::base::base(sp::shared_ptr<neb::core::light::util::parent> parent, ::std::string light_type_string):
	neb::core::light::base(parent),
	light_type_string_(light_type_string),
	ambient_(0.3,0.3,0.3,1.0),
	diffuse_(neb::Color::white<float>()),
	specular_(neb::Color::white<float>())
{
	if(DEBUG_NEB) BOOST_LOG_CHANNEL_SEV(lg, "neb core light", debug) << __PRETTY_FUNCTION__;
}
void neb::gfx::core::light::base::init() {
	if(DEBUG_NEB) BOOST_LOG_CHANNEL_SEV(lg, "neb core light", debug) << __PRETTY_FUNCTION__;

}
void neb::gfx::core::light::base::release() {
	if(DEBUG_NEB) BOOST_LOG_CHANNEL_SEV(lg, "neb core light", debug) << __PRETTY_FUNCTION__;
}
void neb::gfx::core::light::base::cleanup() {
	if(DEBUG_NEB) BOOST_LOG_CHANNEL_SEV(lg, "neb core light", debug) << __PRETTY_FUNCTION__;
}
void neb::gfx::core::light::base::dim() {
	if(DEBUG_NEB) BOOST_LOG_CHANNEL_SEV(lg, "neb core light", debug) << __PRETTY_FUNCTION__;
	/*	
	//printf("diffuse\n");
	//diffuse_.print();

	glLightfv(o_, GL_POSITION, camera_.eye_);
	glLightfv(o_, GL_AMBIENT, ambient_);
	glLightfv(o_, GL_DIFFUSE, diffuse_ * 0.2f);
	glLightfv(o_, GL_SPECULAR, math::black);checkerror(__PRETTY_FUNCTION__);
	*/
	printf("UNSUPPORTED\n");
	exit(0);
}
void		neb::gfx::core::light::base::step(gal::std::timestep const & ts) {

}
void	neb::gfx::core::light::base::draw() {	
	if(DEBUG_NEB) BOOST_LOG_CHANNEL_SEV(lg, "neb core light", debug) << __PRETTY_FUNCTION__;
}
neb::core::pose		neb::gfx::core::light::base::getPose() {
	if(DEBUG_NEB) BOOST_LOG_CHANNEL_SEV(lg, "neb core light", debug) << __PRETTY_FUNCTION__;
	
	auto parent(parent_.lock());
	assert(parent);
	
	auto p = parent->getPoseGlobal();
	
	return p;
}
void			neb::gfx::core::light::base::load(int o, neb::core::pose const & pose) {
	if(DEBUG_NEB) BOOST_LOG_CHANNEL_SEV(lg, "neb core light", debug) << __PRETTY_FUNCTION__;
	
	/** @todo way to ditinguish lights in shader */
	
	auto p = neb::app::base::global()->current_program();
	
	vec3 pos = pos_;
	
	pos += vec3(pose.pos_);
	
	
	p->get_uniform_vector(light_type_string_ + ".position")->load(o, pos);
	
	
	p->get_uniform_vector(light_type_string_ + ".ambient")->load(o, ambient_);
	p->get_uniform_vector(light_type_string_ + ".diffuse")->load(o, diffuse_);
	p->get_uniform_vector(light_type_string_ + ".specular")->load(o, specular_);


}
void	neb::gfx::core::light::base::load_shadow() {
	if(DEBUG_NEB) BOOST_LOG_CHANNEL_SEV(lg, "neb core light", debug) << __PRETTY_FUNCTION__;
	/*	auto p = neb::master::Global()->current_program();

		math::mat44 biasMatrix(
		0.5f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.5f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.5f, 0.0f,
		0.5f, 0.5f, 0.5f, 1.0f);

		math::mat44 textureMatrix = biasMatrix * camera_.proj() * camera_.view();

		uniform_matrix_shadow_.load_matrix4fv(textureMatrix);

	// texture
	glActiveTexture(GL_TEXTURE1);
	texture_shadow_map_.bind();
	uniform_tex_shadow_.load_1i(1);
	*/
}
void	neb::gfx::core::light::base::RenderLightPOV()
{
	if(DEBUG_NEB) BOOST_LOG_CHANNEL_SEV(lg, "neb core light", debug) << __PRETTY_FUNCTION__;
	/*
	   std::shared_ptr<scene> scene = scene_.lock();

	//First pass - from light's point of view
	glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_DEPTH_BUFFER_BIT);

	glDisable(GL_LIGHTING);

	camera_.load_shader();
	*/	/*
		   glMatrixMode(GL_PROJECTION);
		   glLoadMatrixf(camera_.proj());

		   glMatrixMode(GL_MODELVIEW);
		   glLoadMatrixf(camera_.view());

		   glViewport(0, 0, texture_shadow_map_.w_, texture_shadow_map_.h_);
		   */

	//window_->lights_updateGL();

	// Use viewport the same size as the shadow map

	// Draw back faces into the shadow map
	/*	glCullFace(GL_FRONT);

	// Disable color writes, and use flat shading for speed
	glShadeModel(GL_FLAT);
	glColorMask(0, 0, 0, 0);

	//Draw the scene
	scene->draw_shader();

	//Read the depth buffer into the shadow map texture
	texture_shadow_map_.bind();

	glCopyTexSubImage2D(
	GL_TEXTURE_2D,
	0, 0, 0, 0, 0,
	texture_shadow_map_.w_, texture_shadow_map_.h_);

	//restore states
	glCullFace(GL_BACK);
	glShadeModel(GL_SMOOTH);
	glColorMask(1, 1, 1, 1);
	*/
	checkerror("unknown");
}
void	neb::gfx::core::light::base::RenderShadowPost()
{
	//Disable textures and texgen
	glDisable(GL_TEXTURE_2D);

	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
	glDisable(GL_TEXTURE_GEN_R);
	glDisable(GL_TEXTURE_GEN_Q);

	glDisable(GL_ALPHA_TEST);
	checkerror(__PRETTY_FUNCTION__);
}




