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

		class base;
	}
	/** @brief GLSL */
	namespace glsl {
		/** @brief GLSL Uniforms */
		namespace Uniform {
			/** @brief Scalar GLSL Uniforms */
			namespace Scalar {
				class base;
			}
			/** @brief Vector GLSL Uniforms */
			namespace Vector {
				class base;
			}
		}
		class program;
		class shader;
		class attrib;
	}

	/** @brief %Graphics */
	namespace gfx {
		namespace window {
			namespace util {
				class parent;
			}

			class base;
		}

		/** @brief Graphical User Interface */
		namespace gui {
			/** @brief %Layout */
			namespace layout {
				class base;

				/** @brief %utilities */
				namespace util {
					class parent;
				}


			}
			
			/** @brief %Object */
			namespace object {
				/** @brief %utilities */
				namespace util {
					class parent;
				}

				class base;
				class terminal;
			}

		}

		/**@brief %Context */
		namespace context {
			/** @brief %utilities */
			namespace util {
				class parent;
			}
			class base;
		}
		
		/**@brief %environ */
		namespace environ {
			class base;
			class two;
			class three;
		}

		/**@brief %environ */
		namespace drawable {
			class base;
			class two;
			class three;
		}

		/** @brief Camera */
		namespace Camera {
			namespace View {
				class base;
				class Free;
				class Ridealong;

			}
			namespace Projection {
				class base;
				class Perspective;

			}
		}
	}

	/*template<typename>*/ class texture;
}

#endif



