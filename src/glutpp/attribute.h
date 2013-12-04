#ifndef __ATTRIBUTE_H__
#define __ATTRIBUTE_H__

namespace glutpp
{
	class attribute
	{
		public:
			attribute(char const *);
			void		enable();
			void		disable();
			
			char const *	name_;
			GLuint		o_;
	};
}

#endif
