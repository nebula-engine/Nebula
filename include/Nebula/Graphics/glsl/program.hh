#ifndef __DRAW_H__
#define __DRAW_H__

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <map>
#include <vector>

#include <Nebula/config.hh> // Nebula/config.hpp.in
#include <Nebula/Types.hh>
#include <Nebula/Graphics/Types.hh>

//#include <Nebula/Graphics/glsl/attrib.hh>
//#include <Nebula/Graphics/glsl/Uniform/uniform.hh>

namespace neb {
	namespace glsl {
		class shader;

		class program: public std::enable_shared_from_this<program> {
			public:
				program();
				void	init();
				void	add_shader(char const *, GLenum);
				void	add_shaders(std::vector<Neb::glsl::shader>);
				void	compile();
				void	use();
				void	locate();
				void	scanUniforms();

				void	add_attrib(Neb::attrib_name::e, char const *, GLuint);
				void	add_uniform_scalar(std::string, GLenum);
				void	add_uniform_vector(std::string, std::string, GLenum);
				
				
				std::shared_ptr<Neb::glsl::attrib>			get_attrib(int);
				std::shared_ptr<Neb::glsl::Uniform::Scalar::Base>		get_uniform_scalar(std::string);
				std::shared_ptr<Neb::glsl::Uniform::Vector::Base>		get_uniform_vector(std::string);

				//std::shared_ptr<Neb::glsl::uniform>	get_uniform(int,int);

				GLuint	o_;
				
				std::map<std::string, std::shared_ptr<Neb::glsl::Uniform::Scalar::Base> >		uniform_scalar_;
				std::map<std::string, std::shared_ptr<Neb::glsl::Uniform::Vector::Base> >		uniform_vector_;

				std::map<int,std::shared_ptr<attrib> >		attrib_;
		};
	}
}
#endif
