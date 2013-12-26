#ifndef __GLUTPP_ACTOR_H__
#define __GLUTPP_ACTOR_H__
#include <memory>
#include <vector>
#include <map>

#include <math/vec4.h>
#include <math/vec3.h>
#include <math/vec2.h>
#include <math/geo/polyhedron.h>
#include <math/transform.h>

#include <glutpp/types.h>
#include <glutpp/texture.h>
#include <glutpp/material.h>


namespace glutpp
{
	class actor: public std::enable_shared_from_this<actor>
	{
		public:
			actor();
			//void		init(std::shared_ptr<scene>);
			std::shared_ptr<scene>	get_scene();
			
			virtual int	draw(std::shared_ptr<glutpp::window>);
			virtual int	release();
			
			//virtual void	render_reflection();
			
			int		i_;
			
			//texture	texture_image_;
			
			math::transform		pose_;
			
			std::weak_ptr<scene>	scene_;
			
			shape_vec		shapes_;

			std::vector<int>	actors_;
			std::vector<int>	lights_;

			
	};
}

#endif
