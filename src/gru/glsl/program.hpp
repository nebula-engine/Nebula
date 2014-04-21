#ifndef __DRAW_H__
#define __DRAW_H__

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <map>
#include <vector>

#include <gru/master.hpp>
#include <gru/glsl/attrib.hpp>
#include <gru/glsl/uniform.hpp>

namespace glutpp
{
	namespace glsl
	{
		class shader;

		class program: public std::enable_shared_from_this<program>
		{
			public:
				program();
				void	init();
				void	add_shader(char const *, GLenum);
				void	add_shaders(std::vector<glutpp::glsl::shader>);
				void	compile();
				void	use();
				void	locate();

				void	add_attrib(glutpp::attrib_name::e, char const *, GLuint);
				int	add_uniform(glutpp::uniform_name::e, char const *);
				int	add_uniform(glutpp::uniform_name::e, char const *, char const *);
				
				
				std::shared_ptr<glutpp::glsl::attrib>	get_attrib(int);
				std::shared_ptr<glutpp::glsl::uniform>	get_uniform(int);
				//std::shared_ptr<glutpp::glsl::uniform>	get_uniform(int,int);

				GLuint	o_;
				
				std::map<int,std::shared_ptr<uniform> >		uniform_;
				std::map<int,std::shared_ptr<attrib> >		attrib_;
		};
	}
}
#endif
