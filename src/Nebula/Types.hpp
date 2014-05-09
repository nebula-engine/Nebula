#ifndef NEBULA_TYPES_HH
#define NEBULA_TYPES_HH

#include <Nebula/Map.hpp>

/** @brief root namespace for @gru */
namespace Neb {

	class simulation_callback;

	class app;
	class master;

	typedef Neb::weak_ptr<app>	app_w;




	namespace window {
		
		class raw;
		class desc;
		class window;

		typedef std::shared_ptr<window>		window_s;
		typedef std::weak_ptr<window>		window_w;

		typedef std::shared_ptr<desc>		desc_s;

	}



	/** @brief %Shape */	
	namespace Shape {
		struct flag {
			enum e {
				SHOULD_RELEASE = 1 << 0,
				IMAGE          = 1 << 1,
			};
		};

		class id;
		class Raw;
		class desc;
		class base;
		class shape;
		class parent;
		class raw_factory;

		typedef std::shared_ptr<base>		base_s;
		typedef std::shared_ptr<id>		id_s;
		typedef std::shared_ptr<Raw>		raw_s;

		typedef Neb::unique_ptr<desc>		desc_u;


		typedef std::shared_ptr<shape>		shape_s;

		typedef Neb::weak_ptr<base>		base_w;
		typedef Neb::weak_ptr<id>		id_w;

		typedef Neb::weak_ptr<Raw>		Raw_w;
		typedef Neb::unique_ptr<Raw>		Raw_u;


		typedef Neb::weak_ptr<desc>		desc_w;


		typedef Neb::unique_ptr<shape>		shape_u;
		typedef Neb::weak_ptr<shape>		shape_w;
		

		typedef Neb::unique_ptr<parent>		parent_u;
		typedef Neb::weak_ptr<parent>		parent_w;

	}
	/** @brief Lights */
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
		typedef Neb::weak_ptr<desc>	desc_w;


		typedef std::shared_ptr<light>		light_s;
		typedef std::weak_ptr<light>		light_w;
		typedef std::unique_ptr<light>		light_u;

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

		typedef std::shared_ptr<layout>		layout_s;
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

	/** @brief Camera */
	namespace Camera {
		namespace View {
			class Base;
			class Free;
			class Ridealong;
			
			typedef std::shared_ptr<Base>		Base_s;
			typedef Neb::unique_ptr<Base>		Base_u;
			
			typedef std::shared_ptr<Ridealong>	Ridealong_s;
			typedef std::weak_ptr<Ridealong>	Ridealong_w;
		}
		namespace Projection {
			class Base;
			class Perspective;


			typedef Neb::unique_ptr<Base>	Base_u;
		}
	}



	class renderable;

	//typedef Neb::unique_ptr<renderable>	renderable_u;
	typedef Neb::unique_ptr<renderable>	renderable_u;
	typedef Neb::weak_ptr<renderable>	renderable_w;


}

#endif
