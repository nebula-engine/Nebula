#include <stdio.h>

#include <GL/glew.h>

#include <gal/log/log.hpp>

#include <neb/gfx/util/log.hpp>
#include <neb/gfx/glsl/attrib.hh>
#include <neb/gfx/free.hpp>
#include <neb/gfx/glsl/program/base.hpp>

constexpr char const *		neb::gfx::glsl::attribs::string[neb::gfx::glsl::attribs::COUNT];
constexpr char const *		neb::gfx::glsl::uniforms::string[neb::gfx::glsl::uniforms::COUNT];

neb::gfx::glsl::attrib::attrib():
	o_(-1),
	o_bind_(-1)
{}
void	neb::gfx::glsl::attrib::init(char const * name, GLuint o_bind)
{
	name_ = name;
	o_bind_ = o_bind;
	
	LOG(lg, neb::gfx::sl, debug) << "attrib " << name_;
	
}
int	neb::gfx::glsl::attrib::locate(std::shared_ptr<neb::gfx::glsl::program::base> p) {
	glBindAttribLocation(p->o_, o_bind_, name_);
	checkerror("glBindAttribLocation");
	
	assert(o_ == -1);

	o_ = glGetAttribLocation(p->o_, name_);
	
	checkerror("glGetAttribLocation");
	
	printf("%s %s %i\n", __PRETTY_FUNCTION__, name_, o_);
	
	if(o_ == -1)
	{
		printf("could not find attrib '%s'\n", name_);
		abort();
	}
	
	return o_;
}
void	neb::gfx::glsl::attrib::enable()
{
	LOG(lg, neb::gfx::sl, debug) << "enable attrib " << name_;

	glEnableVertexAttribArray(o_);

	checkerror("glEnableVertexAttribArray");
}
void	neb::gfx::glsl::attrib::disable()
{
	glDisableVertexAttribArray(o_);

	checkerror("glDisableVertexAttribArray");
}

