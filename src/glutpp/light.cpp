#include <stdio.h>
#include <glutpp/light.h>
#include <glutpp/window.h>

glutpp::light::light(window* window, GLenum o):
	window_(window),
	o_(o),
	ambient_(math::white * 0.2f),
	diffuse_(math::white),
	specular_(math::white)
{
	printf("%s\n",__FUNCTION__);
	printf("GL_LIGHT %i\n",o_ - GL_LIGHT0);

	glEnable(GL_LIGHTING);
	glEnable(o_);
	
	updateGL();

	int size = 512;

	camera_.fovy_ = 45.0f;
	camera_.w_ = size;
	camera_.h_ = size;
	camera_.zn_ = 1.0f;
	camera_.zf_ = 100.f;
	
	texture_shadow_map_.init(size,size);
}
void	glutpp::light::updateGL()
{
	//printf("diffuse\n");
	//diffuse_.print();
	
	glLightfv(o_, GL_POSITION, camera_.eye_);
	glLightfv(o_, GL_AMBIENT, ambient_);
	glLightfv(o_, GL_DIFFUSE, diffuse_);
	glLightfv(o_, GL_SPECULAR, specular_);	
}
void	glutpp::light::dim()
{
	//printf("diffuse\n");
	//diffuse_.print();
	
	glLightfv(o_, GL_POSITION, camera_.eye_);
	glLightfv(o_, GL_AMBIENT, ambient_);
	glLightfv(o_, GL_DIFFUSE, diffuse_ * 0.2f);
	glLightfv(o_, GL_SPECULAR, math::black);
}
void	glutpp::light::draw()
{

}
void	glutpp::light::RenderShadow()
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

}
void	glutpp::light::RenderLightPOV()
{
	printf("%s\n",__PRETTY_FUNCTION__);
	
	//First pass - from light's point of view
	glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_DEPTH_BUFFER_BIT);

	glDisable(GL_LIGHTING);
	
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(camera_.proj());
	
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(camera_.view());

	glViewport(0, 0, texture_shadow_map_.w_, texture_shadow_map_.h_);

	
	//window_->lights_updateGL();

	// Use viewport the same size as the shadow map
	
	// Draw back faces into the shadow map
	glCullFace(GL_FRONT);
	
	// Disable color writes, and use flat shading for speed
	glShadeModel(GL_FLAT);
	glColorMask(0, 0, 0, 0);
	
	//Draw the scene
	window_->Display();
	
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

}


