#include <GL/glew.h>

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <string.h>

#include <glutpp/glsl/program.h>
#include <glutpp/glsl/shader.h>
#include <glutpp/window.h>

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
	
	for(int i = 0; i < s.size(); ++i )
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
void	glutpp::glsl::program::use()
{
	printf("%s\n",__PRETTY_FUNCTION__);

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
int	glutpp::glsl::program::add_attrib(glutpp::attrib_name::e name, char const * s, GLuint o_bind) {
	std::shared_ptr<glutpp::glsl::attrib> a(new glutpp::glsl::attrib);
	
	a->init(s, o_bind);
	
	attrib_[name] = a;
}
int	glutpp::glsl::program::add_uniform(glutpp::uniform_name::e name, char const * s) {
	std::shared_ptr<glutpp::glsl::uniform> u(new glutpp::glsl::uniform);
	
	u->init(s);
	
	uniform_[name] = u;
}
int	glutpp::glsl::program::add_uniform(glutpp::uniform_name::e name, char const * s1, char const * s2) {
	std::shared_ptr<glutpp::glsl::uniform> u(new glutpp::glsl::uniform);
	
	u->init(s1,s2,20);
	
	uniform_[name] = u;
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
std::shared_ptr<glutpp::glsl::uniform>	glutpp::glsl::program::get_uniform(int name) {
	//printf("%s\n", __PRETTY_FUNCTION__);
	
	auto it = uniform_.find(name);
	
	if(it == uniform_.end())
	{
		printf("uniform %i not found\n",name);
		exit(0);
	}
	
	auto p = (*it).second;
	
	assert(p);
	
	return p;
}
int	glutpp::glsl::program::locate() {

	std::shared_ptr<glutpp::glsl::attrib> attrib;
	
	for(auto it = attrib_.begin(); it != attrib_.end(); ++it)
	{
		attrib = (*it).second;
		
		attrib->locate(shared_from_this());
	}
	
	std::shared_ptr<glutpp::glsl::uniform> uniform;
	
	for(auto it = uniform_.begin(); it != uniform_.end(); ++it)
	{
		uniform = (*it).second;
		
		uniform->locate(shared_from_this());
	}
	
}


