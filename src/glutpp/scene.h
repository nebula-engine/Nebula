#ifndef __GLUTPP_SCENE_H__
#define __GLUTPP_SCENE_H__

#include <vector>

#include <glutpp/uniform.h>
#include <glutpp/camera.h>

#define LIGHT_MAX 20

namespace glutpp
{
	class renderable;
	class object;
	class light;
	class scene: public gal:flag, public std::enable_shared_from_this<scene>
	{
		public:
			enum
			{
				RAY_TRACE			= 1 << 0,
				LIGHTING			= 1 << 1,
				SHADOW				= 1 << 2,
				REFLECT				= 1 << 4,
				REFLECT_PLANAR			= 1 << 5,
				REFLECT_CURVED			= 1 << 6,
				TEX_IMAGE			= 1 << 7,
				TEX_NORMAL_MAP			= 1 << 8,
				SHADER				= 1 << 9
			};
			
			scene();
			void			init(std::shared_ptr<renderable>);
			void			add_object(object*);
			void			add_light(light*);
			void			objects_for_each(std::function<void(glutpp::object*)>);
			void			lights_for_each(std::function<void(glutpp::light*)>);
		
			void			render(double);
			void			draw();

			struct
			{
				uniform		light_count_;
				uniform		model_;
				uniform		view_;
				uniform		proj_;
			} uniforms_;
	
	
			std::weak_ptr<renderable>		renderable_;

			std::vector<std::shared_ptr<object> >	objects_;
	
			camera					camera_;
			
			program*				program_;
			std::vector<shader>			shaders_;
			
			light*					lights_[LIGHT_MAX];
			int					light_count_;

	};
}

#endif



