#ifndef __GLUTPP_BUFFER_H__
#define __GLUTPP_BUFFER_H__

namespace glutpp
{
	class buffer
	{
		public:
			void	init();
			void	bind();
			void	unbind();

			GLuint	o_;
	};
}

#endif

