#ifndef __GLUTPP_CAMERA_CONROL_H__
#define __GLUTPP_CAMERA_CONROL_H__

namespace glutpp
{
	class camera_control
	{
		public:
			
			void	callback_x_(float);
			void	callback_y_(float);
			void	callback_z_(float);

			float	x_;
			float	y_;
			float	z_;
			
			std::vector<sig::connection<void> >	vec_x_;
			std::vector<sig::connection<void> >	vec_y_;
			std::vector<sig::connection<void> >	vec_z_;

	};
}

#endif

