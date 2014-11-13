#ifndef NEBULA_ENUMS_HPP
#define NEBULA_ENUMS_HPP

namespace neb {
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

	struct program_name {
		enum e {
			NONE = 0,
			TEXT,
			QUAD,
			LIGHT,
			IMAGE
		};
	};

	struct attrib_name {
		enum e {
			NONE = 0,
			POSITION,
			NORMAL,
			TEXCOOR,
			COOR
		};
	};

	struct uniform_name {
		enum e {
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
}

#endif
