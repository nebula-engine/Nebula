#ifndef GRU_FREE_HPP
#define GRU_FREE_HPP

#include <memory>
#include <sstream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <gal/stl/helper.hpp>

#include <neb/core/color/Color.hh>

#include <neb/gfx/util/decl.hpp>
#include <neb/gfx/glsl/util/decl.hpp>


namespace neb {
	void	draw_quad(
			std::shared_ptr<neb::gfx::glsl::program::base> p,
			float,
			float,
			float,
			float,
			neb::core::color::color);
	void	draw_text(
			std::shared_ptr<neb::gfx::glsl::program::base> p,
			float,
			float,
			float,
			float,
			neb::core::color::color,
			std::string,
			std::string::size_type pos = std::string::npos);
}

template<typename... T> void	checkerror(char const * cstr, T... t) {

#ifdef _DEBUG
	GLenum err = glGetError();
	if(err != GL_NO_ERROR)
	{
		unsigned char const * str = gluErrorString(err);
		printf(cstr, t...);
		printf("OpenGL Error: %s\n", str);
		fflush(stdout);
		abort();
	}
#endif

}

bool	isGLError();

template<class A> A*	new_copy(std::shared_ptr<A> a) {
	if(a) {
		return new A(*a);
	}
	return NULL;
}

#endif

