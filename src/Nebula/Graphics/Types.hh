#ifndef NEBULA_GRAPHICS_TYPES_HH
#define NEBULA_GRAPHICS_TYPES_HH

namespace Neb {

	struct attrib_name {
		enum e {};
	};
	struct program_name {
		enum e {};
	};


	/** @brief Lights */
	namespace Light {
		struct type {
			enum e {
				POINT,
				DIRECTIONAL,
				SPOT,
			};
		};
		enum {
			light_max = 20
		};

		class raw;
		class desc;
		class light;


		typedef std::unique_ptr<raw>	raw_u;


		typedef std::shared_ptr<desc>	desc_s;
		typedef std::weak_ptr<desc>	desc_w;
		typedef std::unique_ptr<desc>	desc_u;


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

	/** @brief %Graphics */
	namespace Graphics {
		namespace Window {
			namespace Util {
				class Parent;

				typedef std::shared_ptr<Parent>		Parent_s;
				typedef std::weak_ptr<Parent>		Parent_w;

			}
			class Base;

			typedef std::shared_ptr<Base>		Base_s;
			typedef std::weak_ptr<Base>		Base_w;
		}

		/** @brief Graphical User Interface */
		namespace gui {
			class layout;

			typedef std::shared_ptr<layout>		layout_s;
			typedef std::unique_ptr<layout>		layout_u;
			typedef std::weak_ptr<layout>		layout_w;


			namespace object {
				class object;
				class object_factory;
				typedef std::shared_ptr<object>			object_s;
				typedef std::shared_ptr<object_factory>		object_factory_s;

				typedef Neb::Map<object>		object_m;
			}

		}

		/**@brief %Context */
		namespace Context {
			/** @brief %Util */
			namespace Util {
				class Parent;

				typedef std::shared_ptr<Parent>		Parent_s;
				typedef std::weak_ptr<Parent>		Parent_w;
				typedef std::unique_ptr<Parent>		Parent_u;
			}
			class Base;

			//typedef Neb::unique_ptr<renderable>	renderable_u;
			typedef std::unique_ptr<Base>	Base_u;
			typedef std::weak_ptr<Base>	Base_w;
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
			typedef std::unique_ptr<Base>		Base_u;

			typedef std::shared_ptr<Ridealong>	Ridealong_s;
			typedef std::weak_ptr<Ridealong>	Ridealong_w;
		}
		namespace Projection {
			class Base;
			class Perspective;

			typedef std::shared_ptr<Base>		Base_s;
			typedef std::weak_ptr<Base>		Base_w;
			typedef std::unique_ptr<Base>		Base_u;
		}
	}
}

#endif



