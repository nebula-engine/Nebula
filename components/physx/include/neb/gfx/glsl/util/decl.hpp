#ifndef NEB_GFX_GLSL_UTIL_DECL_HPP
#define NEB_GFX_GLSL_UTIL_DECL_HPP

namespace neb { namespace gfx {

	namespace glsl {

		struct attribs {
			enum e {
				COOR,
				TEX,
				POSITION,
				COLOR,
				NORMAL,
				TEXCOOR,
				TANGENT,
				BINORMAL,
				INSTANCE_MODEL0,
				INSTANCE_MODEL1,
				INSTANCE_MODEL2,
				INSTANCE_MODEL3,
				INSTANCE_SAMPLER,
				INSTANCE_DIFFUSE,
				INSTANCE_AMBIENT,
				INSTANCE_SPECULAR,
				INSTANCE_EMISSION,
				INSTANCE_SHININESS,
				COUNT
			};

			static constexpr char const * string[attribs::COUNT] = {
				"coor",
				"tex",
				"position",
				"color",
				"normal",
				"texcoor",
				"tangent",
				"binormal",
				"instance_model_0",
				"instance_model_1",
				"instance_model_2",
				"instance_model_3",
				"instance_sampler",
				"instance_diffuse",
				"instance_ambient",
				"instance_specular",
				"instance_emission",
				"instance_shininess"
			};

		};

		struct uniforms {
			enum e {
				FLAG,
				VIEW,
				PROJ,
				MODEL,
				TEX,
				TEX_IMAGE,
				TEX_NORMAL_MAP,
				TEX_SHADOW_MAP,
				LIGHT_POSITION,
				LIGHT_AMBIENT,
				LIGHT_DIFFUSE,
				LIGHT_SPECULAR,
				LIGHT_ATTEN_CONST,
				LIGHT_ATTEN_LINEAR,
				LIGHT_ATTEN_QUAD,
				LIGHT_SPOT_DIRECTION,
				LIGHT_SPOT_CUTOFF,
				LIGHT_SPOT_EXPONENT,
				LIGHT_SHADOW_VPB_0,
				LIGHT_SHADOW_VPB_1,
				LIGHT_SHADOW_VPB_2,
				LIGHT_SHADOW_VPB_3,
				LIGHT_SHADOW_VPB_4,
				LIGHT_SHADOW_VPB_5,
				LIGHT_SHADOW_SAMPLER_0,
				LIGHT_SHADOW_SAMPLER_1,
				LIGHT_TYPE,
				LIGHT_CLOSED,
				LIGHT_COUNT,
				FONT_COLOR,
				HF_MIN,
				HF_MAX,
				HAS_NORMAL_MAP,
				COUNT
			};


			static constexpr char const * string[uniforms::COUNT] = {
				"flag",
				"view",
				"proj",
				"model",
				"tex",
				"image",
				"normal_map",
				"shadow_map",
				"light_position",
				"light_ambient",
				"light_diffuse",
				"light_specular",
				"light_atten_const",
				"light_atten_linear",
				"light_atten_quad",
				"light_spot_direction",
				"light_spot_cutoff",
				"light_spot_exponent",
				"light_shadow_vpb_0",
				"light_shadow_vpb_1",
				"light_shadow_vpb_2",
				"light_shadow_vpb_3",
				"light_shadow_vpb_4",
				"light_shadow_vpb_5",
				"light_shadow_sampler_0",
				"light_shadow_sampler_1",
				"light_type",
				"light_closed",
				"light_count",
				"font_color",
				"hf_min",
				"hf_max",
				"has_normal_map"
			};
		};

		namespace program {
			class base;
			class threed;
		}

		class shader;

	}

}}

#endif
