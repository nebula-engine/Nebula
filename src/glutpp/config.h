#ifndef __GLUTPP_CONFIG_H__
#define __GLUTPP_CONFIG_H__

#define GLUTPP_INSTALL_DIR "/home/charles/usr"
#define GLUTPP_OBJECT_DIR "/home/charles/usr/include/glutpp/objects"
#define GLUTPP_SHADER_DIR "/home/charles/usr/include/glutpp/glsl/shaders"

#define GLUTPP_DEBUG_0_FUNCTION printf("%s\n", __PRETTY_FUNCTION__)

#define GLUTPP_DEBUG_1_FUNCTION

#include <vector>
#include <memory>

#include <gal/map.h>
#include <gal/sig/connection.h>

typedef std::shared_ptr<gal::sig::connection<int,int,int> >	mouse_button_fun_c;
typedef std::shared_ptr<gal::sig::connection<double,double> >	cursor_pos_fun_c;
typedef std::shared_ptr<gal::sig::connection<int> >		cursor_enter_fun_c;
typedef std::shared_ptr<gal::sig::connection<double,double> >	scroll_fun_c;
typedef std::shared_ptr<gal::sig::connection<int,int,int,int> >	key_fun_c;
typedef std::shared_ptr<gal::sig::connection<unsigned int> >	char_fun_c;

namespace glutpp
{
	namespace network
	{
		enum type
		{
			SCENE,
			ACTIVE_TRANSFORM_SET,
			ACTOR_FORCE,
			ACTOR_CREATE,
			ACTOR_RELEASE,
		};
	}

	struct filter   
	{
		enum type: unsigned int
		{
			NONE = 0,
			STATIC = 1 << 0,
			DYNAMIC = 1 << 1,
			PROJECTILE = 1 << 2,
			UNDRIVABLE_SURFACE = 1 << 3,
		};

		static unsigned int const RIGID_AGAINST = type::STATIC | type::DYNAMIC;

		static unsigned int const DRIVABLE_SURFACE = type::STATIC | type::DYNAMIC;

		static unsigned int const PROJECTILE_AGAINST = type::STATIC | type::DYNAMIC;

		static unsigned int const COLLISION_FLAG_WHEEL = 0;
		static unsigned int const COLLISION_FLAG_WHEEL_AGAINST = 0;
		static unsigned int const COLLISION_FLAG_CHASSIS = type::DYNAMIC;
		static unsigned int const COLLISION_FLAG_CHASSIS_AGAINST = RIGID_AGAINST;

	};

	struct program_name
	{
		enum e
		{
			NONE = 0,
			TEXT,
			QUAD,
			LIGHT,
			IMAGE
		};
	};
	struct attrib_name
	{
		enum e
		{
			NONE = 0,
			POSITION,
			NORMAL,
			TEXCOOR,
			COOR
		};
	};
	struct uniform_name
	{
		enum e
		{
			UNIFORM_NONE = 0,
			COLOR,
			TEX,
			LIGHT_COUNT,
			MODEL,
			VIEW,
			PROJ,
			IMAGE,
			LIGHT_POSITION,
			LIGHT_AMBIENT,
			LIGHT_DIFFUSE,
			LIGHT_SPECULAR,
			LIGHT_SPOT_DIRECTION,
			LIGHT_SPOT_CUTOFF,
			LIGHT_SPOT_EXPONENT,
			LIGHT_SPOT_LIGHT_COS_CUTOFF,
			LIGHT_ATTEN_CONST,
			LIGHT_ATTEN_LINEAR,
			LIGHT_ATTEN_QUAD,
			FRONT_AMBIENT,
			FRONT_DIFFUSE,
			FRONT_SPECULAR,
			FRONT_EMISSION,
			FRONT_SHININESS,
		};
	};


	namespace window
	{	
		struct raw;
		class desc;
		typedef std::shared_ptr<desc>		desc_shared;
		class window;
		typedef std::shared_ptr<window>		window_shared;
		typedef std::weak_ptr<window>		window_weak;
		typedef gal::map<window>		window_map;
	}

	class renderable;
	typedef std::shared_ptr<renderable>	renderable_shared;

	namespace scene
	{
		struct raw;

		class desc;
		typedef std::shared_ptr<desc>		desc_shared;

		class scene;
		typedef std::shared_ptr<scene>		scene_shared;
		typedef std::weak_ptr<scene>		scene_weak;
	}


	class camera;
	typedef std::shared_ptr<camera> camera_shared;

	namespace actor
	{
		struct raw;

		class desc;
		typedef std::shared_ptr<desc>		desc_shared;

		class actor;
		typedef std::shared_ptr<actor>		actor_shared;
		typedef std::weak_ptr<actor>		actor_weak;
		typedef gal::map<actor>			actor_map;
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

		struct raw;

		class desc;
		typedef std::shared_ptr<desc>		desc_shared;

		class shape;
		typedef std::shared_ptr<shape>		shape_shared;
		typedef std::weak_ptr<shape>		shape_weak;
		typedef gal::map<shape>			shape_map;
	}
	namespace light
	{
		struct raw;

		class desc;
		typedef std::shared_ptr<desc>		desc_shared;

		class light;
		typedef std::shared_ptr<light>		light_shared;
		typedef std::shared_ptr<light>		light_weak;
		typedef gal::map<light>			light_map;
	}
	namespace glsl
	{
		class program;
	}
	namespace gui
	{
		class layout;
		typedef std::shared_ptr<layout>		layout_shared;
		typedef gal::map<layout>		layout_map;

		namespace object
		{
			class object;
			class object_factory;
			typedef std::shared_ptr<object>		object_shared;
			typedef gal::map<object>		object_map;
		}
	}
	class texture;







}

#endif
