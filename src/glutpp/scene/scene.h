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
		class scene:
			public std::enable_shared_from_this<scene>,
			public gal::flag<unsigned int>

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
				int				i();
				void				i(int);
				//glutpp::scene::id_shared	id();
				void				init(glutpp::scene::desc_s);
			protected:
				unsigned int			f();
				void				f(unsigned int);
			public:
				void				resize(int,int);

				void				render(
						double,
						glutpp::camera_s,
						glutpp::window::window_s);

				int				draw(glutpp::window::window_s);

				void				write_addr(gal::network::message_shared);
			public:
				int				i_;
				raw				raw_;
				
				glutpp::renderable_weak		renderable_;
				
				gal::map<glutpp::actor::actor>	actors_;
		};
	}
}
#endif



