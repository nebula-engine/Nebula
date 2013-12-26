#ifndef __GLUTPP_TYPES_H__
#define __GLUTPP_TYPES_H__

#include <memory>
#include <vector>

namespace glutpp
{
	enum shape_type
	{
		NONE = 0,
		BOX,
		SPHERE,
	};
	
	
	class window;
	class scene;
	class shape;
	class light;
	namespace glsl
	{
		class program;
	}
	
	typedef std::shared_ptr<window>	window_t;
	typedef std::shared_ptr<shape>	shape_t;
	
	typedef std::vector<shape_t>	shape_vec;
}

#endif
