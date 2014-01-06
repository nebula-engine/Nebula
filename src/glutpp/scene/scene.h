#ifndef __GLUTPP_SCENE_H__
#define __GLUTPP_SCENE_H__

#include <vector>

#include <gal/flag.h>
#include <gal/map.h>

#include <glutpp/config.h>
#include <glutpp/actor/actor.h>
#include <glutpp/camera.h>
//#include <glutpp/shader.h>

#define LIGHT_MAX 20

namespace glutpp
{
	namespace scene
	{
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


				scene(glutpp::scene::desc_shared);
				virtual ~scene();
				void			i(int);
				void			init(std::shared_ptr<renderable>);
			public:
				void			resize(int,int);
				void			render(
						double,
						glutpp::camera_shared,
						glutpp::window::window_shared);

				int			draw(glutpp::window::window_shared);
			public:
				glutpp::scene::desc_shared		desc_;
				gal::map<glutpp::actor::actor>		actors_;
		};
	}
}
#endif



