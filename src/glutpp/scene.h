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
	class scene: public std::enable_shared_from_this<scene>
	{
		public:
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
			} uniforms_;
	
			std::weak_ptr<renderable>	renderable_;

			std::vector<object*>	objects_;

			camera			camera_;
			
			light*			lights_[LIGHT_MAX];
			int			light_count_;

	};
}

#endif



