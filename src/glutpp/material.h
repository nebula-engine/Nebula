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
			material(window*,math::color,math::color,math::color,math::color,float);
			void		load();

			window*		window_;
			
			math::color	ambient_;
			math::color	diffuse_;
			math::color	specular_;
			math::color	emission_;
			float		shininess_;


			uniform		uniform_ambient_;
			uniform		uniform_diffuse_;
			uniform		uniform_specular_;
			uniform		uniform_emission_;
			uniform		uniform_shininess_;
	};
}

#endif
