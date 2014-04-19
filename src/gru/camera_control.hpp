#ifndef __GLUTPP_CAMERA_CONROL_H__
#define __GLUTPP_CAMERA_CONROL_H__

#include <vector>

#include <math/vec3.hpp>

#include <galaxy/sig/connection.hpp>

namespace glutpp
{
	class camera_control
	{
		public:
			virtual math::mat44		supply() = 0;
			double				last_;
	};
	class camera_free: public camera_control {
		public:
			//typedef std::shared_ptr<WINDOW>		WINDOW_S;
			//typedef std::weak_ptr<WINDOW>		WINDOW_W;
			
			camera_free();
			void					init(glutpp::window::window_s);
			
			int					callback_x_(int,float);
			int					callback_y_(int,float);
			int					callback_z_(int,float);

			void					step(double);

			float					pitch_;
			float					yaw_;



			math::vec4					eye_;
			math::vec3<double>				center_;
			math::vec3<double>				look_;
			math::vec3<double>				up_;

			math::vec3<double>				v0_;
			math::vec3<double>				v1_;

			std::vector<gal::sig::connection<>*>		vec_x_;
			std::vector<gal::sig::connection<>*>		vec_y_;
			std::vector<gal::sig::connection<>*>		vec_z_;

			glutpp::window::window_w				window_;
	};
}

#endif

