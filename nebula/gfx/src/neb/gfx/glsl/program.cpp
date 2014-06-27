#include <iostream>

#include <GL/glew.h>

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <string.h>
#include <algorithm>
#include <cassert>

#include <neb/debug.hh>
#include <neb/gfx/glsl/shader.hh>
#include <neb/free.hh>
#include <neb/gfx/glsl/program.hh>
#include <neb/gfx/glsl/attrib.hh>
#include <neb/gfx/glsl/Uniform/scalar.hpp>
#include <neb/gfx/glsl/Uniform/vector.hpp>

neb::glsl::program::program()
{
}
void	neb::glsl::program::init()
{
	//NEBULA_GLSL_PROGRAM_FUNC;

	o_ = glCreateProgram();
	
	printf("program = %i\n",o_);
	
	checkerror("glCreateProgram");
}
void	neb::glsl::program::add_shaders(std::vector<neb::glsl::shader> s)
{
	//GRU_GLSL_PROGRAM_FUNC
	
	for(unsigned int i = 0; i < s.size(); ++i )
	{
		printf("shader %i attached to program %i\n",s[i].o_,o_);
		
		glAttachShader(o_, s.at(i).o_);
		checkerror("glAttachShader");
	}
}
void	neb::glsl::program::add_shader(char const * filename, GLenum type)
{
	neb::glsl::shader s;
	s.load(filename, type);
	
	glAttachShader(o_, s.o_);
	checkerror("glAttachShader");
}
void	neb::glsl::program::compile() {
	//GRU_GLSL_PROGRAM_FUNC
	
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
void	neb::glsl::program::use() {
	
	//GRU_GLSL_PROGRAM_FUNC;
	
	glUseProgram(o_);
	checkerror("glUseProgram");
	
	std::shared_ptr<neb::glsl::attrib> attrib;
	
	for(auto it = attrib_.begin(); it != attrib_.end(); ++it)
	{
		attrib = (*it).second;
		assert(attrib);
		attrib->locate(shared_from_this());
	}
}
void	neb::glsl::program::add_attrib(neb::attrib_name::e name, char const * s, GLuint o_bind) {
	std::shared_ptr<neb::glsl::attrib> a(new neb::glsl::attrib);
	
	a->init(s, o_bind);
	
	attrib_[name] = a;
}
void	neb::glsl::program::add_uniform_scalar(std::string name, GLenum type) {
	
	std::shared_ptr<neb::glsl::Uniform::Scalar::base> u;

	switch(type) {
		case GL_INT:
			u.reset(new neb::glsl::Uniform::Scalar::Int(name));
			break;
		case GL_FLOAT:
			u.reset(new neb::glsl::Uniform::Scalar::Float(name));
			break;
		case GL_FLOAT_VEC3:
			u.reset(new neb::glsl::Uniform::Scalar::Vec3(name));
			break;
		case GL_FLOAT_VEC4:
			u.reset(new neb::glsl::Uniform::Scalar::Vec4(name));
			break;
		case GL_FLOAT_MAT4:
			u.reset(new neb::glsl::Uniform::Scalar::Mat4(name));
			break;
		case GL_SAMPLER_2D:
			u.reset(new neb::glsl::Uniform::Scalar::Sampler2D(name));
			break;
		default:
			printf("unsupported glsl type \"%s\"\n", name.c_str());
			exit(0);
	}

	uniform_scalar_[name] = u;
}
void	neb::glsl::program::add_uniform_vector(std::string name1, std::string name2, GLenum type) {

	std::shared_ptr<neb::glsl::Uniform::Vector::base> u;

	switch(type) {
		case GL_INT:
			u.reset(new neb::glsl::Uniform::Vector::Int(name1, name2));
			break;
		case GL_FLOAT:
			u.reset(new neb::glsl::Uniform::Vector::Float(name1, name2));
			break;
		case GL_FLOAT_VEC3:
			u.reset(new neb::glsl::Uniform::Vector::Vec3(name1, name2));
			break;
		case GL_FLOAT_VEC4:
			u.reset(new neb::glsl::Uniform::Vector::Vec4(name1, name2));
			break;
		default:
			printf("unsupported glsl type \"%s.%s\"\n", name1.c_str(), name2.c_str());
			exit(0);
	}
	
	std::string name = name1 + "." + name2;
	
	uniform_vector_[name] = u;
	
}
std::shared_ptr<neb::glsl::attrib>	neb::glsl::program::get_attrib(int name) {
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
std::shared_ptr<neb::glsl::Uniform::Scalar::base>	neb::glsl::program::get_uniform_scalar(std::string name) {
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
std::shared_ptr<neb::glsl::Uniform::Vector::base>	neb::glsl::program::get_uniform_vector(std::string name) {
	//printf("%s\n", __PRETTY_FUNCTION__);

	auto it = uniform_vector_.find(name);

	if(it == uniform_vector_.end()) {
		
		for(auto it2 = uniform_vector_.begin(); it2 != uniform_vector_.end(); ++it2) {
			std::cout << (*it2).first << std::endl;
		}
		
		printf("uniform \"%s\" not found\n", name.c_str());
		exit(0);
	}

	auto p = (*it).second;

	assert(p);

	return p;
}
void	neb::glsl::program::locate() {

	std::shared_ptr<neb::glsl::attrib> attrib;

	for(auto it = attrib_.begin(); it != attrib_.end(); ++it)
	{
		attrib = (*it).second;

		attrib->locate(shared_from_this());
	}

	{
		std::shared_ptr<neb::glsl::Uniform::Scalar::base> u;
		for(auto it = uniform_scalar_.begin(); it != uniform_scalar_.end(); ++it) {
			u = (*it).second;
			u->locate(shared_from_this());
		}
	}	

	std::shared_ptr<neb::glsl::Uniform::Vector::base> u;
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
	m[GL_INT]		="int";
	m[GL_INT_VEC2]		="ivec2";
	m[GL_INT_VEC3]		="ivec3";
	m[GL_INT_VEC4]		="ivec4";
	m[GL_UNSIGNED_INT]	="unsigned int";
	m[GL_UNSIGNED_INT_VEC2]	="uvec2";
	m[GL_UNSIGNED_INT_VEC3]	="uvec3";
	m[GL_UNSIGNED_INT_VEC4]	="uvec4";
	m[GL_BOOL]				="bool";
	m[GL_BOOL_VEC2]				="bvec2";
	m[GL_BOOL_VEC3]				="bvec3";
	m[GL_BOOL_VEC4]				="bvec4";
	m[GL_FLOAT_MAT2]			="mat2";
	m[GL_FLOAT_MAT3]			="mat3";
	m[GL_FLOAT_MAT4]			="mat4";
	m[GL_FLOAT_MAT2x3]			="mat2x3";
	m[GL_FLOAT_MAT2x4]			="mat2x4";
	m[GL_FLOAT_MAT3x2]			="mat3x2";
	m[GL_FLOAT_MAT3x4]			="mat3x4";
	m[GL_FLOAT_MAT4x2]			="mat4x2";
	m[GL_FLOAT_MAT4x3]			="mat4x3";
	m[GL_DOUBLE_MAT2]			="dmat2";
	m[GL_DOUBLE_MAT3]			="dmat3";
	m[GL_DOUBLE_MAT4]			="dmat4";
//	m[GL_DOUBLE_MAT2x3]			="dmat2x3";
//	m[GL_DOUBLE_MAT2x4]			="dmat2x4";
//	m[GL_DOUBLE_MAT3x2]			="dmat3x2";
//	m[GL_DOUBLE_MAT3x4]			="dmat3x4";
//	m[GL_DOUBLE_MAT4x2]			="dmat4x2";
//	m[GL_DOUBLE_MAT4x3]			="dmat4x3";
	m[GL_SAMPLER_1D]			="sampler1D";
	m[GL_SAMPLER_2D]			="sampler2D";
	m[GL_SAMPLER_3D]			="sampler3D";
	m[GL_SAMPLER_CUBE]			="samplerCube";
	m[GL_SAMPLER_1D_SHADOW]			="sampler1DShadow";
	m[GL_SAMPLER_2D_SHADOW]			="sampler2DShadow";
	m[GL_SAMPLER_1D_ARRAY]			="sampler1DArray";
	m[GL_SAMPLER_2D_ARRAY]			="sampler2DArray";
	m[GL_SAMPLER_1D_ARRAY_SHADOW]			="sampler1DArrayShadow";
	m[GL_SAMPLER_2D_ARRAY_SHADOW]			="sampler2DArrayShadow";
	m[GL_SAMPLER_2D_MULTISAMPLE]			="sampler2DMS";
	m[GL_SAMPLER_2D_MULTISAMPLE_ARRAY]		="sampler2DMSArray";
	m[GL_SAMPLER_CUBE_SHADOW]			="samplerCubeShadow";
	m[GL_SAMPLER_BUFFER]				="samplerBuffer";
	m[GL_SAMPLER_2D_RECT]				="sampler2DRect";
	m[GL_SAMPLER_2D_RECT_SHADOW]			="sampler2DRectShadow";
	m[GL_INT_SAMPLER_1D]				="isampler1D";
	m[GL_INT_SAMPLER_2D]				="isampler2D";
	m[GL_INT_SAMPLER_3D]				="isampler3D";
	m[GL_INT_SAMPLER_CUBE]				="isamplerCube";
	m[GL_INT_SAMPLER_1D_ARRAY]			="isampler1DArray";
	m[GL_INT_SAMPLER_2D_ARRAY]			="isampler2DArray";
	m[GL_INT_SAMPLER_2D_MULTISAMPLE]		="isampler2DMS";
	m[GL_INT_SAMPLER_2D_MULTISAMPLE_ARRAY]		="isampler2DMSArray";
	m[GL_INT_SAMPLER_BUFFER]			="isamplerBuffer";
	m[GL_INT_SAMPLER_2D_RECT]			="isampler2DRect";
	m[GL_UNSIGNED_INT_SAMPLER_1D]			="usampler1D";
	m[GL_UNSIGNED_INT_SAMPLER_2D]			="usampler2D";
	m[GL_UNSIGNED_INT_SAMPLER_3D]			="usampler3D";
	m[GL_UNSIGNED_INT_SAMPLER_CUBE]			="usamplerCube";
	m[GL_UNSIGNED_INT_SAMPLER_1D_ARRAY]		="usampler2DArray";
	m[GL_UNSIGNED_INT_SAMPLER_2D_ARRAY]		="usampler2DArray";
	m[GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE]	="usampler2DMS";
	m[GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE_ARRAY]	="usampler2DMSArray";
	m[GL_UNSIGNED_INT_SAMPLER_BUFFER]		="usamplerBuffer";
	m[GL_UNSIGNED_INT_SAMPLER_2D_RECT]		="usampler2DRect";

	auto it = m.find(type);

	if(it != m.end()) return it->second;

	return "unknown";
}
void		neb::glsl::program::scanUniforms() {
	GLsizei len;
	GLint size;
	GLenum type;
	GLchar str_name[128];
	for(int i = 0; i < 1000; i++) {
		glGetActiveUniform(o_, i, 128, &len, &size, &type, str_name);
		
		if(isGLError()) break;
		
		//printf("name=%32s type=%s\n", str_name, shaderTypeString(type));

		// scalar or vector

		std::string name = str_name;

		size_t find_open = name.find("[");
		size_t find_close = name.find("]");

		if(find_open != std::string::npos) {

			std::string name1 = name.substr(0, find_open);
			std::string name2 = name.substr(find_close + 2);
			
			auto it = uniform_vector_.find(name1 + "." + name2);
			if(it != uniform_vector_.end()) continue;
			
			add_uniform_vector(name1, name2, type);
	
		} else {
			
			add_uniform_scalar(name, type);
		}
	}
}


