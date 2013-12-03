#ifndef __ATTRIBUTE_H__
#define __ATTRIBUTE_H__

namespace glutpp
{
	class attribute
	{
		public:
			attribute();

			char const *	name_;
			GLuint		location_;
	};
}

#endif
