#include <stdio.h>
#include <assert.h>

#include <math/mat44.hpp>

#include <gru/light/light.hpp>
#include <gru/window/window.hpp>
#include <gru/scene/scene.hpp>
#include <gru/shape/shape.hpp>

glutpp::light::light::light(glutpp::shape::shape_s shape):
	shape_(shape)
{
	GLUTPP_DEBUG_0_FUNCTION;
}
unsigned int glutpp::light::light::f() {
	return raw_.flag_;
}
void glutpp::light::light::f(unsigned int flag) {
	raw_.flag_ = flag;
}
void glutpp::light::light::init(/*glutpp::scene::scene_s scene,*/ glutpp::light::desc_s desc) {
	GLUTPP_DEBUG_0_FUNCTION;
	
	//assert(scene);
	assert(desc);
	
	//scene_ = scene;
	
	raw_ = *(desc->get_raw());
	
	/*
	camera_.fovy_ = 45.0f;
	camera_.w_ = 512;
	camera_.h_ = 512;
	camera_.zn_ = 1.0f;
	camera_.zf_ = 100.f;
	*/
	
	//texture_shadow_map_.init_shadow(camera_.w_, camera_.h_);
	
	set(
		glutpp::light::flag::e::SHOULD_LOAD_POS |
		glutpp::light::flag::e::SHOULD_LOAD_SPOT_DIRECTION |
		glutpp::light::flag::e::SHOULD_LOAD_OTHER
	);
}
void glutpp::light::light::release() {
	GLUTPP_DEBUG_0_FUNCTION;
}
void glutpp::light::light::cleanup() {
	GLUTPP_DEBUG_1_FUNCTION;
}
void glutpp::light::light::notify_foundation_change_pose() {
	set(
		glutpp::light::flag::e::SHOULD_LOAD_POS |
		glutpp::light::flag::e::SHOULD_LOAD_SPOT_DIRECTION
	);
}
void glutpp::light::light::dim() {
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
void	glutpp::light::light::draw() {	
	GLUTPP_DEBUG_1_FUNCTION;
}
math::mat44 glutpp::light::light::get_pose() {
	GLUTPP_DEBUG_1_FUNCTION;
	
	assert(!shape_.expired());
	
	math::mat44 m = shape_.lock()->get_pose_global();
	
	return m;
}
void glutpp::light::light::load(int o, math::mat44 space) {
	GLUTPP_DEBUG_1_FUNCTION;
	
	auto p = glutpp::master::Global()->current_program();

	
	
	math::vec4 pos = raw_.pos_;
	pos = space.GetTranslatedVector3D(pos);
	pos.w = raw_.pos_.w;




	math::vec3<double> spot_direction = raw_.spot_direction_;
	
	if(raw_.spot_cutoff_ < (M_PI/2.0))
	{
		//spot_direction.print();
	
		space.RotateVector3D(spot_direction);
	
		//spot_direction.print();
	}
	//pos.print();
	
	
	//if(any(glutpp::light::flag::e::SHOULD_LOAD_POS))
	{
		p->get_uniform(glutpp::uniform_name::e::LIGHT_POSITION)->load_4fv(o, pos);
		
		unset(glutpp::light::flag::e::SHOULD_LOAD_POS);
	}	
	//if(any(glutpp::light::flag::e::SHOULD_LOAD_SPOT_DIRECTION))
	{
		p->get_uniform(glutpp::uniform_name::e::LIGHT_SPOT_DIRECTION)->load_3fv(
				o, spot_direction);
		
		unset(glutpp::light::flag::e::SHOULD_LOAD_SPOT_DIRECTION);
	}
	
	//if(any(glutpp::light::flag::e::SHOULD_LOAD_OTHER))
	{
		p->get_uniform(glutpp::uniform_name::e::LIGHT_AMBIENT)->load_4fv(
				o, raw_.ambient_);
		p->get_uniform(glutpp::uniform_name::e::LIGHT_DIFFUSE)->load_4fv(
				o, raw_.diffuse_);
		p->get_uniform(glutpp::uniform_name::e::LIGHT_SPECULAR)->load_4fv(
				o, raw_.specular_);
			
		p->get_uniform(glutpp::uniform_name::e::LIGHT_SPOT_CUTOFF)->load(
				o, raw_.spot_cutoff_);
		p->get_uniform(glutpp::uniform_name::e::LIGHT_SPOT_EXPONENT)->load(
				o, raw_.spot_exponent_);
		p->get_uniform(glutpp::uniform_name::e::LIGHT_SPOT_LIGHT_COS_CUTOFF)->load(
				o, raw_.spot_light_cos_cutoff_);
		p->get_uniform(glutpp::uniform_name::e::LIGHT_ATTEN_CONST)->load(
				o, raw_.atten_const_);
		p->get_uniform(glutpp::uniform_name::e::LIGHT_ATTEN_LINEAR)->load(
				o, raw_.atten_linear_);
		p->get_uniform(glutpp::uniform_name::e::LIGHT_ATTEN_QUAD)->load(
				o, raw_.atten_quad_);

		unset(glutpp::light::flag::e::SHOULD_LOAD_OTHER);
	}
}
void	glutpp::light::light::load_shadow() {
	GLUTPP_DEBUG_1_FUNCTION;
	/*	auto p = glutpp::master::Global()->current_program();

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
void	glutpp::light::light::RenderLightPOV()
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
void	glutpp::light::light::RenderShadowPost()
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
void glutpp::light::light::i(int ni) {
	GLUTPP_DEBUG_0_FUNCTION;

	i_ = ni;
}






