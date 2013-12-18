#ifndef __GLUTPP_SCENE_H__
#define __GLUTPP_SCENE_H__

#include <vector>

#include <gal/flag.h>
#include <gal/map.h>

//#include <glutpp/uniform.h>
#include <glutpp/actor.h>
#include <glutpp/camera.h>
//#include <glutpp/shader.h>

#define LIGHT_MAX 20

namespace glutpp
{
	class renderable;
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
			virtual ~scene();
			void			init(std::shared_ptr<renderable>);
			
			
			int			prepare();
			
			void			add_actor(std::shared_ptr<glutpp::actor>);
			void			add_light(std::shared_ptr<light>);
	//		void			objects_for_each(std::function<void(glutpp::object*)>);
	//		void			lights_for_each(std::function<void(glutpp::light*)>);
		
			void			resize(int,int);

			void			render_shader_light(double);
			void			render_no_shader_light(double);
			
			
			void			draw();
			
			
			std::weak_ptr<renderable>		renderable_;
			
			gal::map<actor>				actors_;
			gal::map<light>				lights_;
	};
}

#endif



