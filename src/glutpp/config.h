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
#include <gal/network/vector.h>

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
		class type_ext;
		enum type
		{
			SCENE_CREATE,
			ACTOR_CREATE,
			ACTOR_UPDATE,
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
		typedef std::shared_ptr<desc>		desc_s;
		class window;
		typedef std::shared_ptr<window>		window_s;
		typedef std::weak_ptr<window>		window_w;
		typedef gal::map<window>		window_m;
	}


	namespace scene
	{
		struct raw;

		struct id;
		typedef std::shared_ptr<id>	id_s;

		struct addr;
		typedef std::shared_ptr<addr>	addr_s;

		class desc;
		typedef std::shared_ptr<desc>	desc_s;

		class scene;
		typedef std::shared_ptr<scene>	scene_s;
		typedef std::weak_ptr<scene>	scene_w;
	}
	namespace actor
	{
		struct id;
		typedef std::shared_ptr<id>		id_s;

		struct addr;
		typedef std::shared_ptr<addr>		addr_s;

		struct raw;
		typedef std::shared_ptr<raw>		raw_s;
		typedef gal::network::vector<raw>	raw_v;

		class desc;
		typedef std::shared_ptr<desc>		desc_s;

		class actor;
		typedef std::shared_ptr<actor>		actor_s;
		typedef std::weak_ptr<actor>		actor_w;
		typedef gal::map<actor>			actor_m;
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
		
		struct id;
		typedef std::shared_ptr<id>		id_s;
		
		struct raw;
		typedef std::shared_ptr<raw>		raw_s;

		class desc;
		typedef std::shared_ptr<desc>		desc_s;

		class shape;
		typedef std::shared_ptr<shape>		shape_s;
		typedef std::weak_ptr<shape>		shape_w;
		typedef gal::map<shape>			shape_m;
	}
	namespace light
	{
		enum
		{
			light_max = 20
		};

		struct raw;

		class desc;
		typedef std::shared_ptr<desc>		desc_s;

		class light;
		typedef std::shared_ptr<light>		light_s;
		typedef std::shared_ptr<light>		light_w;
		typedef gal::map<light>			light_m;
	}
	namespace glsl
	{
		class program;
	}
	namespace gui
	{
		class layout;
		typedef std::shared_ptr<layout>		layout_s;
		typedef gal::map<layout>		layout_m;

		namespace object
		{
			class object;
			class object_factory;
			typedef std::shared_ptr<object>		object_s;
			typedef gal::map<object>		object_m;
		}
	}
	class texture;
	class camera;
	typedef std::shared_ptr<camera> camera_s;


	class renderable;
	typedef std::shared_ptr<renderable>	renderable_shared;
	typedef std::weak_ptr<renderable>	renderable_weak;





}

#endif
