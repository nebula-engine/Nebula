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
			}

			class Base;
		}

		/** @brief Graphical User Interface */
		namespace gui {
			/** @brief %Layout */
			namespace Layout {
				class Base;

				/** @brief %utilities */
				namespace Util {
					class Parent;
				}


			}
			
			/** @brief %Object */
			namespace object {
				/** @brief %utilities */
				namespace Util {
					class Parent;
				}

				class Base;
				class terminal;
			}

		}

		/**@brief %Context */
		namespace Context {
			/** @brief %Util */
			namespace Util {
				class Parent;
			}
			class Base;
		}

		/** @brief Camera */
		namespace Camera {
			namespace View {
				class Base;
				class Free;
				class Ridealong;

			}
			namespace Projection {
				class Base;
				class Perspective;

			}
		}
	}

	/*template<typename>*/ class texture;
}

#endif



