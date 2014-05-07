#ifndef NEBULA_TYPES_HH
#define NEBULA_TYPES_HH

#include <Nebula/Map.hpp>

/** @brief root namespace for @gru */
namespace Neb {

	class simulation_callback;

	class app;
	class master;

	typedef Neb::weak_ptr<app>	app_w;

	namespace network {
		enum type {
			NONE           = 0x0,
			SCENE_CREATE   = 0x1,
			ACTOR_CREATE   = 0x2,
			ACTOR_UPDATE   = 0x3,
			ACTOR_EVENT    = 0x4,
			CONTROL_CREATE = 0x5,
			CONTROL_UPDATE = 0x6,
		};
	}
	

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


	namespace window {
		
		class raw;
		class desc;
		class window;

		typedef std::shared_ptr<window>		window_s;
		typedef Neb::weak_ptr<window>		window_w;
		typedef std::shared_ptr<desc>		desc_s;

	}


	namespace Scene {
		enum flag {
			SHOULD_RELEASE = 1 << 0
		};

		class raw;
		class addr;
		class desc;

		class scene;
		
		typedef Neb::weak_ptr<raw>		raw_w;
		typedef Neb::weak_ptr<addr>		addr_w;
		typedef Neb::weak_ptr<desc>		desc_w;

		typedef Neb::unique_ptr<scene>		scene_u;
		typedef Neb::weak_ptr<scene>		scene_w;
	}
	
	namespace Shape {
		struct type {
			enum e {
				NONE = 0,
				BOX,
				SPHERE,
				EMPTY
			};
		};
		struct flag {
			enum e {
				SHOULD_RELEASE = 1 << 0,
				IMAGE          = 1 << 1,
			};
		};

		class id;
		class raw;
		class raw_base;
		class desc;
		class base;
		class shape;
		class parent;
		class raw_factory;

		typedef std::shared_ptr<base>		base_s;
		typedef std::shared_ptr<id>		id_s;
		typedef std::shared_ptr<raw>		raw_s;
		typedef std::shared_ptr<raw_base>	raw_base_s;

		typedef Neb::unique_ptr<desc>		desc_u;


		typedef std::shared_ptr<shape>		shape_s;
		typedef std::shared_ptr<raw_factory>	raw_factory_s;

		typedef Neb::weak_ptr<base>		base_w;
		typedef Neb::weak_ptr<id>		id_w;
		typedef Neb::weak_ptr<raw>		raw_w;
		typedef Neb::weak_ptr<desc>		desc_w;


		typedef Neb::unique_ptr<shape>		shape_u;
		typedef Neb::weak_ptr<shape>		shape_w;
		

		typedef Neb::unique_ptr<parent>		parent_u;
		typedef Neb::weak_ptr<parent>		parent_w;

	}
	namespace light {
		struct type {
			enum e {
				POINT,
				DIRECTIONAL,
				SPOT,
			};
		};
		struct flag
		{
			enum e {
				SHOULD_DELETE              = 1 << 0,
				SHOULD_LOAD_POS            = 1 << 1,
				SHOULD_LOAD_SPOT_DIRECTION = 1 << 2,
				SHOULD_LOAD_OTHER          = 1 << 3,
			};
		};
		enum
		{
			light_max = 20
		};

		class raw;
		class desc;
		class light;


		typedef Neb::unique_ptr<raw>	raw_u;
		typedef Neb::unique_ptr<desc>	desc_u;


		typedef Neb::unique_ptr<light>	light_u;

	}
	/** @brief GLSL */
	namespace glsl {
		/** @brief GLSL Uniforms */
		namespace Uniform {
			/** @brief Scalar GLSL Uniforms */
			namespace Scalar {
				class Base;
			}
			/** @brief Vector GLSL Uniforms */
			namespace Vector {
				class Base;
			}
		}
		class program;
		class shader;
		class attrib;
	}
	/** @brief Graphical User Interface */
	namespace gui {
		class layout;
		
		typedef Neb::unique_ptr<layout>		layout_u;
		typedef Neb::weak_ptr<layout>		layout_w;


		namespace object {
			class object;
			class object_factory;
			typedef std::shared_ptr<object>			object_s;
			typedef std::shared_ptr<object_factory>		object_factory_s;

			typedef Neb::Map<object>		object_m;
		}

	}


	/*template<typename>*/ class texture;

	namespace Camera {
		namespace View {
			class Base;
			class Free;
			class Ridealong;
			
			typedef Neb::unique_ptr<Base>	Base_u;

		}
		namespace Projection {
			class Base;
			class Perspective;


			typedef Neb::unique_ptr<Base>	Base_u;
		}
	}



	class renderable;

	typedef Neb::unique_ptr<renderable>	renderable_u;
	typedef Neb::weak_ptr<renderable>	renderable_w;


}

#endif
