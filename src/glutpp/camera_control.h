#ifndef __GLUTPP_CAMERA_CONROL_H__
#define __GLUTPP_CAMERA_CONROL_H__

#include <vector>

#include <math/vec3.h>

#include <sig/connection.h>

namespace glutpp
{
	class window;
	class camera_control
	{
		public:
			void					init(window*);
			
			int					callback_x_(int,float);
			int					callback_y_(int,float);
			int					callback_z_(int,float);

			math::vec3				v0_;
			math::vec3				v1_;
		
			std::vector<sig::connection<>*>		vec_x_;
			std::vector<sig::connection<>*>		vec_y_;
			std::vector<sig::connection<>*>		vec_z_;

			window*					window_;
	};
}

#endif

