#ifndef __GLUTPP_CONFIG_H__
#define __GLUTPP_CONFIG_H__

#define GLUTPP_INSTALL_DIR "/home/charles/usr"
#define GLUTPP_OBJECT_DIR "/home/charles/usr/include/glutpp/objects"
#define GLUTPP_SHADER_DIR "/home/charles/usr/include/glutpp/glsl/shaders"

#define GLUTPP_DEBUG_0_FUNCTION printf("%s\n", __PRETTY_FUNCTION__)

#define GLUTPP_DEBUG_1_FUNCTION

#include <vector>
#include <memory>

namespace glutpp
{
	class window;

	class scene;
	
	namespace actor
	{
		struct raw;
		class desc;
		class actor;
		
		typedef std::shared_ptr<actor>		actor_shared;
		typedef std::weak_ptr<actor>		actor_weak;
		typedef std::vector<actor_shared>	actor_vec;
	}

	namespace shape
	{

		enum type
		{
			NONE = 0,
			BOX,
			SPHERE,
			EMPTY
		};

		class shape;
		typedef std::shared_ptr<shape>		shape_shared;
		typedef std::weak_ptr<shape>		shape_weak;
		typedef std::vector<shape_shared>	shape_vec;
	}
	namespace light
	{
		class light;
	}
	namespace glsl
	{
		class program;
	}





	typedef std::shared_ptr<window>		window_t;


	typedef std::shared_ptr<shape::shape>	shape_t;
	typedef std::shared_ptr<light::light>	light_t;

	typedef std::vector<shape_t>		shape_vec;
	typedef std::vector<light_t>		light_vec;
}

#endif
