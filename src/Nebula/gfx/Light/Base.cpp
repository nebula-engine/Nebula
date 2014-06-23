#include <stdio.h>
#include <assert.h>

#include <Nebula/app/Base.hh>
#include <Nebula/util/decl.hpp>
#include <Nebula/core/light/Base.hh>
#include <Nebula/gfx/window/Base.hh>
#include <Nebula/core/scene/Base.hh>
#include <Nebula/core/shape/Base.hh>
#include <Nebula/free.hh>
#include <Nebula/gfx/glsl/Uniform/vector.hpp>


neb::Light::base::base(sp::shared_ptr<neb::Light::util::parent> parent, ::std::string light_type_string):
	parent_(parent),
	light_type_string_(light_type_string),
	pos_(vec4(0.0, 0.0, 0.0, 1.0)),
	ambient_(0.3,0.3,0.3,1.0),
	diffuse_(neb::Color::white<float>()),
	specular_(neb::Color::white<float>())
{
	GLUTPP_DEBUG_0_FUNCTION;
}
void neb::Light::base::init() {
	GLUTPP_DEBUG_0_FUNCTION;

}
void neb::Light::base::release() {
	GLUTPP_DEBUG_0_FUNCTION;
}
void neb::Light::base::cleanup() {
	GLUTPP_DEBUG_1_FUNCTION;
}
void neb::Light::base::dim() {
	GLUTPP_DEBUG_1_FUNCTION;
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
void		neb::Light::base::step(gal::std::timestep const & ts) {

}
void	neb::Light::base::draw() {	
	GLUTPP_DEBUG_1_FUNCTION;
}
neb::core::pose		neb::Light::base::getPose() {
	GLUTPP_DEBUG_1_FUNCTION;

	auto p = parent_->getPoseGlobal();

	return p;
}
void			neb::Light::base::load(int o, neb::core::pose const & pose) {
	GLUTPP_DEBUG_1_FUNCTION;
	
	/** @todo way to ditinguish lights in shader */
	
	auto p = neb::app::base::global()->current_program();
	
	vec3 pos = pos_;
	
	pos += vec3(pose.pos_);
	
	
	p->get_uniform_vector(light_type_string_ + ".position")->load(o, pos);
	
	
	p->get_uniform_vector(light_type_string_ + ".ambient")->load(o, ambient_);
	p->get_uniform_vector(light_type_string_ + ".diffuse")->load(o, diffuse_);
	p->get_uniform_vector(light_type_string_ + ".specular")->load(o, specular_);


}
void	neb::Light::base::load_shadow() {
	GLUTPP_DEBUG_1_FUNCTION;
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
void	neb::Light::base::RenderLightPOV()
{
	GLUTPP_DEBUG_1_FUNCTION;
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
void	neb::Light::base::RenderShadowPost()
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




