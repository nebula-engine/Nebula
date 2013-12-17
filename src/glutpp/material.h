#ifndef __GLUTPP_MATERIAL_H__
#define __GLUTPP_MATERIAL_H__

#include <math/color.h>

#include <glutpp/uniform.h>

namespace glutpp
{
	class window;
	class material
	{
		public:
			material();
			void		init(std::shared_ptr<scene>);
			void		load();

			std::weak_ptr<scene>	scene_;

			math::color		ambient_;
			math::color		diffuse_;
			math::color		specular_;
			math::color		emission_;
			float			shininess_;

			struct
			{
				uniform		ambient_;
				uniform		diffuse_;
				uniform		specular_;
				uniform		emission_;
				uniform		shininess_;
			} uniforms_;
	};
}

#endif
