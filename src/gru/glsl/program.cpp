#include <GL/glew.h>

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <string.h>
#include <algorithm>

#include <gru/glsl/program.hpp>
#include <gru/glsl/shader.hpp>
#include <gru/window/window.hpp>

glutpp::glsl::program::program()
{
}
void	glutpp::glsl::program::init()
{
	printf("%s\n",__PRETTY_FUNCTION__);

	o_ = glCreateProgram();
	
	printf("program = %i\n",o_);
	
	checkerror("glCreateProgram");
}
void	glutpp::glsl::program::add_shaders(std::vector<glutpp::glsl::shader> s)
{
	printf("%s\n",__PRETTY_FUNCTION__);
	
	for(unsigned int i = 0; i < s.size(); ++i )
	{
		printf("shader %i attached to program %i\n",s[i].o_,o_);
		
		glAttachShader(o_, s.at(i).o_);
		checkerror("glAttachShader");
	}
}
void	glutpp::glsl::program::add_shader(char const * filename, GLenum type)
{
	glutpp::glsl::shader s;
	s.load(filename, type);
	
	glAttachShader(o_, s.o_);
	checkerror("glAttachShader");
}
void	glutpp::glsl::program::compile() {
	printf("%s\n",__PRETTY_FUNCTION__);
	
	glLinkProgram(o_);
	checkerror("glLinkProgram");
	
	GLint blen = 0;	
	GLsizei slen = 0;
	
	glGetProgramiv(o_, GL_INFO_LOG_LENGTH , &blen);
	
	checkerror("glGetProgramiv");

	if (blen > 1)
	{
		GLchar* compiler_log = (GLchar*)malloc(blen);

		glGetInfoLogARB(o_, blen, &slen, compiler_log);
		printf("compiler_log:%s\n", compiler_log);
		free (compiler_log);
	}

	printf("program=%i\n",o_);

}
void	glutpp::glsl::program::use() {
	
	GLUTPP_DEBUG_1_FUNCTION;
	
	glUseProgram(o_);
	checkerror("glUseProgram");
	
	std::shared_ptr<glutpp::glsl::attrib> attrib;
	
	for(auto it = attrib_.begin(); it != attrib_.end(); ++it)
	{
		attrib = (*it).second;
		assert(attrib);
		attrib->locate(shared_from_this());
	}
}
void	glutpp::glsl::program::add_attrib(glutpp::attrib_name::e name, char const * s, GLuint o_bind) {
	std::shared_ptr<glutpp::glsl::attrib> a(new glutpp::glsl::attrib);
	
	a->init(s, o_bind);
	
	attrib_[name] = a;
}
void	glutpp::glsl::program::add_uniform_scalar(char const * name, GLenum type) {
	
	std::shared_ptr<glutpp::glsl::Uniform::Scalar::Base> u;

	switch(type) {
		case GL_INT:
			u.reset(new glutpp::glsl::Uniform::Scalar::Int);
			break;
	}

	u->init(name);

	uniform_scalar_[name] = u;
}
void	glutpp::glsl::program::add_uniform_vector(char const * name1, char const * name2, GLenum type) {

	std::shared_ptr<glutpp::glsl::Uniform::Scalar::Base> u;

	switch(type) {
		case GL_INT:
			u.reset(new glutpp::glsl::Uniform::Scalar::Int);
			break;
	}
	
	char* name = new char[strlen(name1) + strlen(name2) + 1];
	
	u->init(name);
	
	
	
	uniform_scalar_[name] = u;
	
}
std::shared_ptr<glutpp::glsl::attrib>	glutpp::glsl::program::get_attrib(int name) {
	auto it = attrib_.find(name);

	if(it == attrib_.end())
	{
		printf("attribute %i not found\n",name);
		exit(0);
	}

	auto p = (*it).second;

	assert(p);

	return p;
}
std::shared_ptr<glutpp::glsl::Uniform::Scalar::Base>	glutpp::glsl::program::get_uniform_scalar(std::string name) {
	//printf("%s\n", __PRETTY_FUNCTION__);

	auto it = uniform_scalar_.find(name);

	if(it == uniform_scalar_.end())
	{
		printf("uniform \"%s\" not found\n", name.c_str());
		exit(0);
	}

	auto p = (*it).second;

	assert(p);

	return p;
}
std::shared_ptr<glutpp::glsl::Uniform::Vector::Base>	glutpp::glsl::program::get_uniform_vector(std::string name) {
	//printf("%s\n", __PRETTY_FUNCTION__);

	auto it = uniform_vector_.find(name);

	if(it == uniform_vector_.end())
	{
		printf("uniform \"%s\" not found\n", name.c_str());
		exit(0);
	}

	auto p = (*it).second;

	assert(p);

	return p;
}
void	glutpp::glsl::program::locate() {

	std::shared_ptr<glutpp::glsl::attrib> attrib;

	for(auto it = attrib_.begin(); it != attrib_.end(); ++it)
	{
		attrib = (*it).second;

		attrib->locate(shared_from_this());
	}

	{
		std::shared_ptr<glutpp::glsl::Uniform::Scalar::Base> u;
		for(auto it = uniform_scalar_.begin(); it != uniform_scalar_.end(); ++it) {
			u = (*it).second;
			u->locate(shared_from_this());
		}
	}	

	std::shared_ptr<glutpp::glsl::Uniform::Vector::Base> u;
	for(auto it = uniform_vector_.begin(); it != uniform_vector_.end(); ++it) {
		u = (*it).second;
		u->locate(shared_from_this());
	}
}
char const * shaderTypeString(GLenum type) {
	std::map<GLenum,char const *> m;

	m[GL_FLOAT]		="float";
	m[GL_FLOAT_VEC2]	="vec2";
	m[GL_FLOAT_VEC3]	="vec3";
	m[GL_FLOAT_VEC4]	="vec4";
	m[GL_DOUBLE]		="double";
	m[GL_DOUBLE_VEC2]	="dvec2";
	m[GL_DOUBLE_VEC3]	="dvec3";
	m[GL_DOUBLE_VEC4] 	="dvec4";
	/*
	   GL_INT 	int
	   GL_INT_VEC2 	ivec2​
	   GL_INT_VEC3 	ivec3​
	   GL_INT_VEC4 	ivec4​
	   GL_UNSIGNED_INT 	unsigned int​
	   GL_UNSIGNED_INT_VEC2 	uvec2​
	   GL_UNSIGNED_INT_VEC3 	uvec3​
	   GL_UNSIGNED_INT_VEC4 	uvec4​
	   GL_BOOL 	bool
	   GL_BOOL_VEC2 	bvec2​
	   GL_BOOL_VEC3 	bvec3​
	   GL_BOOL_VEC4 	bvec4​
	   GL_FLOAT_MAT2 	mat2​
	   GL_FLOAT_MAT3 	mat3​
	   GL_FLOAT_MAT4 	mat4​
	   GL_FLOAT_MAT2x3 	mat2x3
	   GL_FLOAT_MAT2x4 	mat2x4​
	   GL_FLOAT_MAT3x2 	mat3x2​
	   GL_FLOAT_MAT3x4 	mat3x4​
	   GL_FLOAT_MAT4x2 	mat4x2​
	   GL_FLOAT_MAT4x3 	mat4x3​
	   GL_DOUBLE_MAT2 	dmat2​
	   GL_DOUBLE_MAT3 	dmat3​
	   GL_DOUBLE_MAT4 	dmat4​
	   GL_DOUBLE_MAT2x3 	dmat2x3​
	   GL_DOUBLE_MAT2x4 	dmat2x4​
	   GL_DOUBLE_MAT3x2 	dmat3x2​
	   GL_DOUBLE_MAT3x4 	dmat3x4​
	   GL_DOUBLE_MAT4x2 	dmat4x2​
	   GL_DOUBLE_MAT4x3 	dmat4x3​
	   GL_SAMPLER_1D 	sampler1D​
	   GL_SAMPLER_2D 	sampler2D​
	   GL_SAMPLER_3D 	sampler3D​
	   GL_SAMPLER_CUBE 	samplerCube​
	   GL_SAMPLER_1D_SHADOW 	sampler1DShadow​
	   GL_SAMPLER_2D_SHADOW 	sampler2DShadow​
	   GL_SAMPLER_1D_ARRAY 	sampler1DArray​
	   GL_SAMPLER_2D_ARRAY 	sampler2DArray​
	   GL_SAMPLER_1D_ARRAY_SHADOW 	sampler1DArrayShadow​
	   GL_SAMPLER_2D_ARRAY_SHADOW 	sampler2DArrayShadow​
	   GL_SAMPLER_2D_MULTISAMPLE 	sampler2DMS​
	   GL_SAMPLER_2D_MULTISAMPLE_ARRAY 	sampler2DMSArray​
	   GL_SAMPLER_CUBE_SHADOW 	samplerCubeShadow​
	   GL_SAMPLER_BUFFER 	samplerBuffer​
	   GL_SAMPLER_2D_RECT 	sampler2DRect​
	   GL_SAMPLER_2D_RECT_SHADOW 	sampler2DRectShadow​
	   GL_INT_SAMPLER_1D 	isampler1D​
	   GL_INT_SAMPLER_2D 	isampler2D​
	   GL_INT_SAMPLER_3D 	isampler3D​
	   GL_INT_SAMPLER_CUBE 	isamplerCube​
	   GL_INT_SAMPLER_1D_ARRAY 	isampler1DArray​
	   GL_INT_SAMPLER_2D_ARRAY 	isampler2DArray​
	   GL_INT_SAMPLER_2D_MULTISAMPLE 	isampler2DMS​
	   GL_INT_SAMPLER_2D_MULTISAMPLE_ARRAY 	isampler2DMSArray​
	   GL_INT_SAMPLER_BUFFER 	isamplerBuffer​
	   GL_INT_SAMPLER_2D_RECT 	isampler2DRect​
	   GL_UNSIGNED_INT_SAMPLER_1D 	usampler1D​
	   GL_UNSIGNED_INT_SAMPLER_2D 	usampler2D​
	   GL_UNSIGNED_INT_SAMPLER_3D​ 	usampler3D​
	   GL_UNSIGNED_INT_SAMPLER_CUBE​ 	usamplerCube​
	   GL_UNSIGNED_INT_SAMPLER_1D_ARRAY​ 	usampler2DArray​
	   GL_UNSIGNED_INT_SAMPLER_2D_ARRAY​ 	usampler2DArray​
	   GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE​ 	usampler2DMS​
	   GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE_ARRAY​ 	usampler2DMSArray​
	   GL_UNSIGNED_INT_SAMPLER_BUFFER​ 	usamplerBuffer​
	   GL_UNSIGNED_INT_SAMPLER_2D_RECT​ 	usampler2DRect​
	 */
	auto it = m.find(type);

	if(it != m.end()) return it->second;

	return "unknown";
}
void		glutpp::glsl::program::scanUniforms() {
	GLsizei len;
	GLint size;
	GLenum type;
	GLchar name[16];
	for(int i = 0; i < 1000; i++) {
		glGetActiveUniform(o_, i, 16, &len, &size, &type, name);
		checkerror("glGetActiveUniform");
		printf("name=%16s type=%s\n",name,shaderTypeString(type));
	}
}


