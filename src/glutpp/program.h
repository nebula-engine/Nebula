#ifndef __DRAW_H__
#define __DRAW_H__


#include <GLFW/glfw3.h>

#include <vector>

namespace glutpp
{
	class shader;
	
	class program
	{
		public:
			program();
			void	init();
			void	add_shaders(std::vector<glutpp::shader>);
			void	compile();
			void	use();
			
			GLuint	o_;
	};
}

#endif
