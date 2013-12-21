#include <stdio.h>
#include <assert.h>

#include <math/mat44.h>

#include <glutpp/light.h>
#include <glutpp/window.h>
#include <glutpp/scene.h>

glutpp::light::light():
	ambient_(math::white * 0.2f),
	diffuse_(math::white),
	specular_(math::white),
	o_(-1),
	spot_direction_(0.0, 0.0, -1.0),
	spot_cutoff_(10.0),
	spot_exponent_(1.0),
	atten_const_(1.0),
	atten_linear_(0.0),
	atten_quad_(0.0)
{

}
void	glutpp::light::init(std::shared_ptr<scene> scene, int o)
{
	printf("%s\n",__PRETTY_FUNCTION__);
	
	scene_ = scene;
	o_ = o;
	
	camera_.fovy_ = 45.0f;
	camera_.w_ = 512;
	camera_.h_ = 512;
	camera_.zn_ = 1.0f;
	camera_.zf_ = 100.f;
	
	printf("GL_LIGHT%i\n",o_);
	
	glEnable(GL_LIGHTING); checkerror("glEnable lighting");
	glEnable(GL_LIGHT0 + o_); checkerror("glEnable light");
	
	texture_shadow_map_.init_shadow(camera_.w_, camera_.h_);
	
	uniforms();

	printf("%s exit\n",__PRETTY_FUNCTION__);

}
void	glutpp::light::uniforms()
{
	printf("%s\n",__PRETTY_FUNCTION__);
	
	assert(o_ != -1);
	
	std::shared_ptr<scene> scene = scene_.lock();

/*	
	p->get_uniform(glutpp::uniform_name::e::POSITION_.init(
			scene,"lights","position",o_);
	p->get_uniform(glutpp::uniform_name::e::AMBIENT_.init(
			scene,"lights","ambient",o_);
	p->get_uniform(glutpp::uniform_name::e::DIFFUSE_.init(
			scene,"lights","diffuse",o_);
	p->get_uniform(glutpp::uniform_name::e::SPECULAR_.init(
			scene,"lights","specular",o_);
	p->get_uniform(glutpp::uniform_name::e::SPOT_DIRECTION_.init(
			scene,"lights","spot_direction",o_);
	p->get_uniform(glutpp::uniform_name::e::SPOT_CUTOFF_.init(
			scene,"lights","spot_cutoff",o_);
	p->get_uniform(glutpp::uniform_name::e::SPOT_EXPONENT_.init(
			scene,"lights","spot_exponent",o_);
	p->get_uniform(glutpp::uniform_name::e::SPOT_LIGHT_COS_CUTOFF_.init(
			scene,"lights","spot_light_cos_cutoff",o_);
	p->get_uniform(glutpp::uniform_name::e::ATTEN_CONST_.init(
			scene,"lights","atten_const",o_);
	p->get_uniform(glutpp::uniform_name::e::ATTEN_LINEAR_.init(
			scene,"lights","atten_linear",o_);
	p->get_uniform(glutpp::uniform_name::e::ATTEN_QUAD_.init(
			scene,"lights","atten_quad",o_);
*/
/*	p->get_uniform(glutpp::uniform_name::e::matrix_shadow_.init(
			scene,"lights","",o_);
	p->get_uniform(glutpp::uniform_name::e::tex_shadow_.init(
	scene,"lights","atten_quad",o_);
 */


	printf("%s exit\n",__PRETTY_FUNCTION__);

}
void	glutpp::light::dim()
{
	printf("%s\n",__PRETTY_FUNCTION__);
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
void	glutpp::light::draw()
{

}
math::vec4	glutpp::light::get_pose()
{
	math::vec4 pos = camera_.eye_;
	
	if(!actor_.expired())
	{
		pos = math::mat44(actor_.lock()->pose_) * pos;
	}
	
	return pos;
}
void		glutpp::light::load_shader()
{
	//printf("%s\n",__PRETTY_FUNCTION__);
	
	auto p = glutpp::__master.current_program();
	
	math::vec4 pos = get_pose();
	
	p->get_uniform(glutpp::uniform_name::e::LIGHT_POSITION)->load_4fv(			o_, pos);
	p->get_uniform(glutpp::uniform_name::e::LIGHT_AMBIENT)->load_4fv(			o_, ambient_);
	p->get_uniform(glutpp::uniform_name::e::LIGHT_DIFFUSE)->load_4fv(			o_, diffuse_);
	p->get_uniform(glutpp::uniform_name::e::LIGHT_SPECULAR)->load_4fv(			o_, specular_);
	p->get_uniform(glutpp::uniform_name::e::LIGHT_SPOT_DIRECTION)->load_3fv(		o_, spot_direction_);
	p->get_uniform(glutpp::uniform_name::e::LIGHT_SPOT_CUTOFF)->load(			o_, spot_cutoff_);
	p->get_uniform(glutpp::uniform_name::e::LIGHT_SPOT_EXPONENT)->load(			o_, spot_exponent_);
	p->get_uniform(glutpp::uniform_name::e::LIGHT_SPOT_LIGHT_COS_CUTOFF)->load(		o_, spot_light_cos_cutoff_);
	p->get_uniform(glutpp::uniform_name::e::LIGHT_ATTEN_CONST)->load(			o_, atten_const_);
	p->get_uniform(glutpp::uniform_name::e::LIGHT_ATTEN_LINEAR)->load(			o_, atten_linear_);
	p->get_uniform(glutpp::uniform_name::e::LIGHT_ATTEN_QUAD)->load(			o_, atten_quad_);

}

void	glutpp::light::load_no_shader()
{


	glLightfv(GL_LIGHT0 + o_, GL_POSITION, camera_.eye_);
	checkerror("glLightfv pos");
	glLightfv(GL_LIGHT0 + o_, GL_AMBIENT, ambient_);
	checkerror("glLightfv amb");
	glLightfv(GL_LIGHT0 + o_, GL_DIFFUSE, diffuse_);
	checkerror("glLightfv dif");
	glLightfv(GL_LIGHT0 + o_, GL_SPECULAR, specular_);
	checkerror("glLightfv spe");
	glLightfv(GL_LIGHT0 + o_, GL_SPOT_DIRECTION, spot_direction_);
	checkerror("glLightfv spe");
	glLightf( GL_LIGHT0 + o_, GL_SPOT_EXPONENT, spot_exponent_);
	checkerror("glLightfv spe");
	glLightf( GL_LIGHT0 + o_, GL_SPOT_CUTOFF, spot_cutoff_);
	checkerror("glLightfv spe");
	glLightf( GL_LIGHT0 + o_, GL_CONSTANT_ATTENUATION, atten_const_);
	checkerror("glLightfv spe");
	glLightf( GL_LIGHT0 + o_, GL_LINEAR_ATTENUATION, atten_linear_);
	checkerror("glLightfv spe");
	glLightf( GL_LIGHT0 + o_, GL_QUADRATIC_ATTENUATION, atten_quad_);
	checkerror("glLightfv spe");
}
void	glutpp::light::load_shadow()
{
	/*	auto p = glutpp::__master.current_program();

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
void	glutpp::light::RenderLightPOV()
{
	printf("%s\n",__PRETTY_FUNCTION__);

	std::shared_ptr<scene> scene = scene_.lock();

	//First pass - from light's point of view
	glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_DEPTH_BUFFER_BIT);

	glDisable(GL_LIGHTING);

	camera_.load_shader();
	/*
	   glMatrixMode(GL_PROJECTION);
	   glLoadMatrixf(camera_.proj());

	   glMatrixMode(GL_MODELVIEW);
	   glLoadMatrixf(camera_.view());

	   glViewport(0, 0, texture_shadow_map_.w_, texture_shadow_map_.h_);
	 */

	//window_->lights_updateGL();

	// Use viewport the same size as the shadow map

	// Draw back faces into the shadow map
	glCullFace(GL_FRONT);

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

	checkerror("unknown");
}
void	glutpp::light::RenderShadowPost()
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


