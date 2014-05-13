#include <stdio.h>
#include <assert.h>

#include <Nebula/Types.hpp>
#include <Nebula/Graphics/light/light.hpp>
#include <Nebula/Graphics/window/window.hpp>
#include <Nebula/Scene/scene.hpp>
#include <Nebula/shape/shape.hpp>
#include <Nebula/free.hpp>
#include <Nebula/Graphics/glsl/Uniform/uniform.hpp>


Neb::light::light::light(Neb::Light::Util::Parent_s parent):
	parent_(parent),
	i_(-1),
	flag_(0),
	pos_(physx::PxVec4(0.0, 0.0, 0.0, 1.0)),
	ambient_(Neb::Color::black<float>()),
	diffuse_(Neb::Color::white<float>()),
	specular_(Neb::Color::white<float>()),
	spot_direction_(physx::PxVec3(0.0, 0.0, -1.0)),
	spot_cutoff_(10.0),
	spot_exponent_(1.0),
	spot_light_cos_cutoff_(1.0),
	atten_const_(1.0),
	atten_linear_(0.0),
	atten_quad_(0.0)
{
	GLUTPP_DEBUG_0_FUNCTION;
}
unsigned int Neb::light::light::f() {
	return raw_.flag_;
}
void Neb::light::light::f(unsigned int flag) {
	raw_.flag_ = flag;
}
void Neb::light::light::init(/*boost::shared_ptr<Neb::scene::scene> scene,*/ boost::shared_ptr<Neb::light::desc> desc) {
	GLUTPP_DEBUG_0_FUNCTION;
	
	//assert(scene);
	assert(desc);
	
	//scene_ = scene;
	
	raw_ = desc->raw_;
	
	/*
	camera_.fovy_ = 45.0f;
	camera_.w_ = 512;
	camera_.h_ = 512;
	camera_.zn_ = 1.0f;
	camera_.zf_ = 100.f;
	*/
	
	//texture_shadow_map_.init_shadow(camera_.w_, camera_.h_);
	
	set(
		Neb::light::flag::e::SHOULD_LOAD_POS |
		Neb::light::flag::e::SHOULD_LOAD_SPOT_DIRECTION |
		Neb::light::flag::e::SHOULD_LOAD_OTHER
	);
}
void Neb::light::light::release() {
	GLUTPP_DEBUG_0_FUNCTION;
}
void Neb::light::light::cleanup() {
	GLUTPP_DEBUG_1_FUNCTION;
}
void Neb::light::light::notify_foundation_change_pose() {
	set(
		Neb::light::flag::e::SHOULD_LOAD_POS |
		Neb::light::flag::e::SHOULD_LOAD_SPOT_DIRECTION
	);
}
void Neb::light::light::dim() {
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
void	Neb::light::light::draw() {	
	GLUTPP_DEBUG_1_FUNCTION;
}
physx::PxMat44		Neb::light::light::get_pose() {
	GLUTPP_DEBUG_1_FUNCTION;
	
	assert(!shape_.expired());
	
	physx::PxMat44 m = shape_.lock()->getPoseGlobal();
	
	return m;
}
void Neb::light::light::load(int o, physx::PxMat44 space) {
	GLUTPP_DEBUG_1_FUNCTION;
	
	auto p = Neb::master::Global()->current_program();

	physx::PxVec4 pos = raw_.pos_;

	pos += physx::PxVec4(space.getPosition(), 0);

	pos.w = raw_.pos_.w;

	physx::PxVec3 spot_direction = raw_.spot_direction_;
	
	if(raw_.spot_cutoff_ < (M_PI/2.0))
	{
		//spot_direction.print();
	
		space.rotate(spot_direction);
	
		//spot_direction.print();
	}
	//pos.print();
	
	
	//if(any(Neb::light::flag::e::SHOULD_LOAD_POS))
	{
		p->get_uniform_vector("lights.position")->load(o, pos);
		
		//unset(Neb::light::flag::e::SHOULD_LOAD_POS);
	}	
	//if(any(Neb::light::flag::e::SHOULD_LOAD_SPOT_DIRECTION))
	{
		p->get_uniform_vector("lights.spot_direction")->load(o, spot_direction);
		
		//unset(Neb::light::flag::e::SHOULD_LOAD_SPOT_DIRECTION);
	}
	
	//if(any(Neb::light::flag::e::SHOULD_LOAD_OTHER))
	{
		p->get_uniform_vector("lights.ambient")->load(o, raw_.ambient_);
		p->get_uniform_vector("lights.diffuse")->load(o, raw_.diffuse_);
		p->get_uniform_vector("lights.specular")->load(o, raw_.specular_);
		p->get_uniform_vector("lights.spot_cutoff")->load(o, raw_.spot_cutoff_);
		p->get_uniform_vector("lights.spot_exponent")->load(o, raw_.spot_exponent_);
		p->get_uniform_vector("lights.spot_light_cos_cutoff")->load(o, raw_.spot_light_cos_cutoff_);
		p->get_uniform_vector("lights.atten_const")->load(o, raw_.atten_const_);
		p->get_uniform_vector("lights.atten_linear")->load(o, raw_.atten_linear_);
		p->get_uniform_vector("lights.atten_quad")->load(o, raw_.atten_quad_);

		//unset(Neb::light::flag::e::SHOULD_LOAD_OTHER);
	}
}
void	Neb::light::light::load_shadow() {
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
void	Neb::light::light::RenderLightPOV()
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
void	Neb::light::light::RenderShadowPost()
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
void Neb::light::light::i(int ni) {
	GLUTPP_DEBUG_0_FUNCTION;

	i_ = ni;
}






