#include <stdio.h>
#include <glutpp/light.h>
#include <glutpp/window.h>


glutpp::light::light(window* window,int o):
	window_(window),
	ambient_(math::white * 0.2f),
	diffuse_(math::white),
	specular_(math::white),
	texture_shadow_map_(window),
	o_(o),
	camera_(window),
	uniform_position_(window,"lights","position",o),
	uniform_ambient_(window,"lights","ambient",o),
	uniform_diffuse_(window,"lights","diffuse",o),
	uniform_specular_(window,"lights","specular",o),
	uniform_spot_direction_(window,"lights","spot_direction",o),
	uniform_spot_cutoff_(window,"lights","spot_cutoff",o),
	uniform_spot_exponent_(window,"lights","spot_exponent",o),
	uniform_spot_light_cos_cutoff_(window,"lights","spot_light_cos_cutoff",o),
	uniform_atten_const_(window,"lights","atten_const",o),
	uniform_atten_linear_(window,"lights","atten_linear",o),
	uniform_atten_quad_(window,"lights","atten_quad",o),
	spot_cutoff_(10),
	spot_exponent_(1),
	atten_const_(1.0),
	atten_linear_(0.0),
	atten_quad_(0.0)
{
	printf("%s\n",__PRETTY_FUNCTION__);

	camera_.fovy_ = 45.0f;
	camera_.w_ = 512;
	camera_.h_ = 512;
	camera_.zn_ = 1.0f;
	camera_.zf_ = 100.f;

	printf("GL_LIGHT%i\n",o_);

	glEnable(GL_LIGHTING); checkerror("glEnable lighting");
	glEnable(GL_LIGHT0 + o_); checkerror("glEnable light");

	updateGL();

	texture_shadow_map_.init_shadow(camera_.w_, camera_.h_);
}
void	glutpp::light::updateGL()
{
	printf("%s\n",__PRETTY_FUNCTION__);

	if(0)//!isset(SHADERS))
	{
	}
}
void	glutpp::light::dim()
{
	//printf("diffuse\n");
	//diffuse_.print();

	glLightfv(o_, GL_POSITION, camera_.eye_);
	glLightfv(o_, GL_AMBIENT, ambient_);
	glLightfv(o_, GL_DIFFUSE, diffuse_ * 0.2f);
	glLightfv(o_, GL_SPECULAR, math::black);checkerror(__PRETTY_FUNCTION__);
}
void	glutpp::light::draw()
{

}
void	glutpp::light::load()
{
	if(window_->all(LIGHTING))
	{
		if(window_->all(SHADER))
		{
			uniform_position_.load_4fv(			camera_.eye_);
			uniform_ambient_.load_4fv(			ambient_);
			uniform_diffuse_.load_4fv(			diffuse_);
			uniform_specular_.load_4fv(			specular_);
			uniform_spot_direction_.load_3fv(		spot_direction_);
			uniform_spot_cutoff_.load_1f(			spot_cutoff_);
			uniform_spot_exponent_.load_1f(			spot_exponent_);
			uniform_spot_light_cos_cutoff_.load_1f(		spot_light_cos_cutoff_);
			uniform_atten_const_.load_1f(			atten_const_);
			uniform_atten_linear_.load_1f(			atten_linear_);
			uniform_atten_quad_.load_1f(			atten_quad_);
		}
		else
		{
			glLightfv(GL_LIGHT0 + o_, GL_POSITION, camera_.eye_);		checkerror("glLightfv pos");
			glLightfv(GL_LIGHT0 + o_, GL_AMBIENT, ambient_);		checkerror("glLightfv amb");
			glLightfv(GL_LIGHT0 + o_, GL_DIFFUSE, diffuse_);		checkerror("glLightfv dif");
			glLightfv(GL_LIGHT0 + o_, GL_SPECULAR, specular_);		checkerror("glLightfv spe");
			glLightfv(GL_LIGHT0 + o_, GL_SPOT_DIRECTION, spot_direction_);	checkerror("glLightfv spe");
			glLightf( GL_LIGHT0 + o_, GL_SPOT_EXPONENT, spot_exponent_);	checkerror("glLightfv spe");
			glLightf( GL_LIGHT0 + o_, GL_SPOT_CUTOFF, spot_cutoff_);	checkerror("glLightfv spe");
			glLightf( GL_LIGHT0 + o_, GL_CONSTANT_ATTENUATION, const_);	checkerror("glLightfv spe");
			glLightf( GL_LIGHT0 + o_, GL_LINEAR_ATTENUATION, atten_linear_);	checkerror("glLightfv spe");
			glLightf( GL_LIGHT0 + o_, GL_QUADRATIC_ATTENUATION, atten_quad_);	checkerror("glLightfv spe");
		}
	}
}
void	glutpp::light::draw_shadow_no_shader()
{
	printf("%s\n",__PRETTY_FUNCTION__);
	
	//Calculate texture matrix for projection
	//This matrix takes us from eye space to the light's clip space
	//It is postmultiplied by the inverse of the current view matrix when specifying texgen

	//bias from [-1, 1] to [0, 1]
	static math::mat44 biasMatrix(
			0.5f, 0.0f, 0.0f, 0.0f,
			0.0f, 0.5f, 0.0f, 0.0f,
			0.0f, 0.0f, 0.5f, 0.0f,
			0.5f, 0.5f, 0.5f, 1.0f);

	math::mat44 textureMatrix = biasMatrix * camera_.proj() * camera_.view();

	//Set up texture coordinate generation.
	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
	glTexGenfv(GL_S, GL_EYE_PLANE, textureMatrix.GetRow(0));
	glEnable(GL_TEXTURE_GEN_S);

	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
	glTexGenfv(GL_T, GL_EYE_PLANE, textureMatrix.GetRow(1));
	glEnable(GL_TEXTURE_GEN_T);

	glTexGeni(GL_R, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
	glTexGenfv(GL_R, GL_EYE_PLANE, textureMatrix.GetRow(2));
	glEnable(GL_TEXTURE_GEN_R);

	glTexGeni(GL_Q, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
	glTexGenfv(GL_Q, GL_EYE_PLANE, textureMatrix.GetRow(3));
	glEnable(GL_TEXTURE_GEN_Q);

	//Bind & enable shadow map texture
	texture_shadow_map_.bind();
	glEnable(GL_TEXTURE_2D);

	//Enable shadow comparison
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE_ARB, GL_COMPARE_R_TO_TEXTURE);

	//Shadow comparison should be true (ie not in shadow) if r<=texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC_ARB, GL_LEQUAL);

	//Shadow comparison should generate an INTENSITY result
	glTexParameteri(GL_TEXTURE_2D, GL_DEPTH_TEXTURE_MODE_ARB, GL_INTENSITY);

	//Set alpha test to discard false comparisons
	glAlphaFunc(GL_GEQUAL, 0.99f);
	glEnable(GL_ALPHA_TEST);
	checkerror(__PRETTY_FUNCTION__);
}
void	glutpp::light::RenderLightPOV()
{
	printf("%s\n",__PRETTY_FUNCTION__);

	//First pass - from light's point of view
	glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_DEPTH_BUFFER_BIT);

	glDisable(GL_LIGHTING);
	
	camera_.load();
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
	window_->display();
	
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


