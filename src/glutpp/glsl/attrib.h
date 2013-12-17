#ifndef __GLUTPP_ATTRIBUTE_H__
#define __GLUTPP_ATTRIBUTE_H__

#include <memory>

namespace glutpp
{
	namespace glsl
	{
		class program;
		class attrib
		{
			public:
				attrib();
				void		init(char const *);
				int		locate(std::shared_ptr<glutpp::glsl::program> p);
				void		enable();
				void		disable();

				char const *	name_;
				GLuint		o_;
		};
	}
}

#endif
