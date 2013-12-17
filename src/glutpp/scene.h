#ifndef __GLUTPP_SCENE_H__
#define __GLUTPP_SCENE_H__

#include <vector>

#include <gal/flag.h>

//#include <glutpp/uniform.h>
#include <glutpp/camera.h>
//#include <glutpp/shader.h>

#define LIGHT_MAX 20

namespace glutpp
{
	class renderable;
	class object;
	class light;
	class program;
	class shader;
	class scene: public gal::flag, public std::enable_shared_from_this<scene>
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
			int			prepare();
			//void			shaders();
			//void			uniforms();
			//GLint			get_program();

			void			add_object(std::shared_ptr<object>);
			void			add_light(std::shared_ptr<light>);
			void			objects_for_each(std::function<void(glutpp::object*)>);
			void			lights_for_each(std::function<void(glutpp::light*)>);
		
			void			resize(int,int);

			//void			render(double);
			void			render_shader_light(double);
			void			render_no_shader_light(double);


			void			draw();
			

/*	
			struct
			{
				uniform		light_count_;
				uniform		model_;
				uniform		view_;
				uniform		proj_;
			} uniforms_;
*/	
	
			std::weak_ptr<renderable>		renderable_;

			std::vector<std::shared_ptr<object> >	objects_;
	
			camera					camera_;
			
			
			std::shared_ptr<light>			lights_[LIGHT_MAX];
			int					light_count_;

	};
}

#endif



