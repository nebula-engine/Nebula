#ifndef NEBULA_GRAPHICS_TYPES_HH
#define NEBULA_GRAPHICS_TYPES_HH

#include <memory>

namespace neb {

	struct attrib_name {
		enum e {
			COOR,
			TEX,
			POSITION,
			NORMAL,
			TEXCOOR,
		};
	};
	struct program_name {
		enum e {
			TEXT,
			LIGHT,
			IMAGE,
		};
	};


	/** @brief Lights */
	namespace Light {
		enum {
			light_max = 20
		};

		class Base;

		typedef std::shared_ptr<Base>		Base_s;
		typedef std::weak_ptr<Base>		Base_w;
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
	namespace gfx {
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
		namespace GUI {
			/** @brief %Layout */
			namespace Layout {
				class Base;

				typedef std::shared_ptr<Base>		Base_s;
				typedef std::weak_ptr<Base>		Base_w;
			}
			
			/** @brief %Object */
			namespace Object {
				namespace Util {
					class Parent;

					typedef std::shared_ptr<Parent>		Parent_s;
					typedef std::weak_ptr<Parent>		Parent_w;
				}

				class Base;
				class terminal;

				typedef std::shared_ptr<Base>		Base_s;
				typedef std::weak_ptr<Base>		Base_w;
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

			typedef std::shared_ptr<Base>	Base_s;
			typedef std::weak_ptr<Base>	Base_w;
		}

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

	/*template<typename>*/ class texture;
}

#endif



