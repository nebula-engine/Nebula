#ifndef __GLUTPP_ATTRIBUTE_H__
#define __GLUTPP_ATTRIBUTE_H__

#include <memory>
#include <Nebula/util/typedef.hpp>

namespace neb {
	namespace glsl {
		class program;
		class attrib {
			public:
				attrib();
				void		init(char const *, GLuint);
				int		locate(sp::shared_ptr<neb::glsl::program> p);
				void		enable();
				void		disable();

				char const *	name_;
				GLuint		o_;
				GLuint		o_bind_;
		};
	}
}

#endif
