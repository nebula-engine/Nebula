#ifndef __DRAW_H__
#define __DRAW_H__


#include <GL/glew.h>
#include <GL/glut.h>

namespace glutpp
{
	class shader;
	
	class program
	{
		public:
			program();
			void	init();
			void	add_shader(glutpp::shader*);
			void	compile();
			void	use();
			
			GLuint	o_;
	};
}

#endif
