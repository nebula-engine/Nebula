
#include <GL/glew.h>
#include <GL/glut.h>

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
void	glutpp::glsl::program::compile()
{
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
}
int	glutpp::glsl::program::add_attrib(glutpp::attrib_name::e n, char const * s)
{
	std::shared_ptr<glutpp::glsl::attrib> a(new glutpp::glsl::attrib);
	
	a->init(s);
}
int	glutpp::glsl::program::add_uniform(glutpp::uniform_name::e, char const * s)
{
	std::shared_ptr<glutpp::glsl::uniform> u(new glutpp::glsl::uniform);
	
	u->init(s);
}
int	glutpp::glsl::program::add_uniform(glutpp::uniform_name::e, char const * s1, char const * s2)
{
	std::shared_ptr<glutpp::glsl::uniform> u(new glutpp::glsl::uniform);
	
	u->init(s1,s2,20);
}
std::shared_ptr<glutpp::glsl::attrib>	glutpp::glsl::program::get_attrib(int name)
{
	auto it = attrib_.find(name);
	
	if(it == attrib_.end())
	{
		printf("uniform %i not found\n",name);
		exit(0);
	}
	
	auto p = (*it).second;
	
	assert(p);
	
	return p;
}
std::shared_ptr<glutpp::glsl::uniform>	glutpp::glsl::program::get_uniform(int name)
{
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



