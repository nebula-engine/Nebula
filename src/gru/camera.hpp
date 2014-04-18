#ifndef __GLUTPP_CAMERA_H__
#define __GLUTPP_CAMERA_H__

#include <vector>
#include <memory>

#include <gal/sig/connection.h>

#include <math/vec3.h>
#include <math/vec4.h>
#include <math/mat44.h>

#include <gru/config.hpp>
#include <gru/camera_control.hpp>

namespace glutpp
{
	class camera
	{
		public:
			camera();
			//void		init(glutpp::renderable_shared);
			math::mat44	proj();
			math::mat44	view();

			void		load();

			void		step(float);
		
			int		north(float);


	
			//std::weak_ptr<renderable>		renderable_;
				
			float					fovy_;
			float					zn_;
			float					zf_;
			int					w_;
			int					h_;
			
			math::vec4				eye_;


		//	std::vector<sig::connection<float>*>	connection_u_;
		//	std::vector<sig::connection<float>*>	connection_v_;
		//	std::vector<sig::connection<float>*>	connection_w_;
			
			std::shared_ptr<camera_control>		control_;
	};
}

#endif
