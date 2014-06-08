#include <stdio.h>
#include <assert.h>

#include <Nebula/App/Base.hh>
#include <Nebula/Types.hh>
#include <Nebula/Graphics/Light/Base.hh>
#include <Nebula/Graphics/Window/Base.hh>
#include <Nebula/Scene/Base.hh>
#include <Nebula/Shape/Base.hh>
#include <Nebula/free.hh>
#include <Nebula/Graphics/glsl/Uniform/uniform.hh>


Neb::Light::Base::Base(Neb::Light::Util::Parent_s parent):
	parent_(parent),
	pos_(physx::PxVec4(0.0, 0.0, 0.0, 1.0)),
	ambient_(Neb::Color::black<float>()),
	diffuse_(Neb::Color::white<float>()),
	specular_(Neb::Color::white<float>()),
	atten_const_(1.0),
	atten_linear_(0.0),
	atten_quad_(0.0)
{
	GLUTPP_DEBUG_0_FUNCTION;
}
void Neb::Light::Base::init() {
	GLUTPP_DEBUG_0_FUNCTION;
	
}
void Neb::Light::Base::release() {
	GLUTPP_DEBUG_0_FUNCTION;
}
void Neb::Light::Base::cleanup() {
	GLUTPP_DEBUG_1_FUNCTION;
}
void Neb::Light::Base::dim() {
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
void		Neb::Light::Base::step(double const & time, double const & ) {
	
}
void	Neb::Light::Base::draw() {	
	GLUTPP_DEBUG_1_FUNCTION;
}
physx::PxMat44		Neb::Light::Base::get_pose() {
	GLUTPP_DEBUG_1_FUNCTION;
	
	physx::PxMat44 m = parent_->getPoseGlobal();
	
	return m;
}
void Neb::Light::Base::load(int o, physx::PxMat44 space) {
	GLUTPP_DEBUG_1_FUNCTION;

	/** @todo way to ditinguish lights in shader */

	auto p = Neb::App::Base::globalBase()->current_program();

	physx::PxVec4 pos = pos_;

	pos += physx::PxVec4(space.getPosition(), 0);

	pos.w = pos_.w;

	
	
	
	//if(any(Neb::light::flag::e::SHOULD_LOAD_POS))
	{
		p->get_uniform_vector("lights.position")->load(o, pos);
		
		//unset(Neb::light::flag::e::SHOULD_LOAD_POS);
	}	
	//if(any(Neb::light::flag::e::SHOULD_LOAD_SPOT_DIRECTION))
	{
		//unset(Neb::light::flag::e::SHOULD_LOAD_SPOT_DIRECTION);
	}
	
	//if(any(Neb::light::flag::e::SHOULD_LOAD_OTHER))
	{
		p->get_uniform_vector("lights.ambient")->load(o, ambient_);
		p->get_uniform_vector("lights.diffuse")->load(o, diffuse_);
		p->get_uniform_vector("lights.specular")->load(o, specular_);
		p->get_uniform_vector("lights.atten_const")->load(o, atten_const_);
		p->get_uniform_vector("lights.atten_linear")->load(o, atten_linear_);
		p->get_uniform_vector("lights.atten_quad")->load(o, atten_quad_);

		//unset(Neb::light::flag::e::SHOULD_LOAD_OTHER);
	}
}
void	Neb::Light::Base::load_shadow() {
	GLUTPP_DEBUG_1_FUNCTION;
	/*	auto p = Neb::master::Global()->current_program();

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
void	Neb::Light::Base::RenderLightPOV()
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
void	Neb::Light::Base::RenderShadowPost()
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




