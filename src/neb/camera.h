#ifndef __NEB_CAMERA_H__
#define __NEB_CAMERA_H__

#include <memory>
#include <map>

//#include <JSL/Event.h>

#include <glutpp/window.h>
#include <glutpp/camera_control.h>


namespace neb
{
	class view;
	namespace actor
	{
		class Base;
	}
	class camera_ridealong: public glutpp::camera_control
	{
		public:
			camera_ridealong();
			virtual math::mat44			supply();
			std::shared_ptr<neb::actor::Base>	actor_;
	};
	class camera: public glutpp::camera_control
	{
		public:
			enum flag
			{
				NORTH = 1 << 0,
				SOUTH = 1 << 1,
				EAST = 1 << 2,
				WEST = 1 << 3
			};

			camera();
			void		Connect();
			void		delete_scene();
			void		SetWindow(glutpp::window*);
			void		Display();
			void		Look();
			physx::PxVec3		Move();
			void			Step(float);
			virtual math::mat44	supply();

			int	FirstOrderDeltaPitchRel(int);
			int	FirstOrderDeltaYawRel(int);		

			int	FirstOrderDeltaPitchAbs(float);
			int	FirstOrderDeltaYawAbs(float);		

			int	HandleAbsNorth(float);
			int	HandleAbsEast(float);

			int	HandleKeyNorth(int);
			int	HandleKeySouth(int);
			int	HandleKeyEast(int);
			int	HandleKeyWest(int);

			int	handle_delete_scene(int);

			neb::view* view_;

			unsigned int	flag_;

			float pitch_;
			float yaw_;
			float v_pitch_;
			float v_yaw_;


			float north_;
			float east_;

			physx::PxVec3 eye_;

			std::map<int,unsigned int>		key_flag_;
			std::map<int,physx::PxVec3>	head_;
			std::map<unsigned int,int>		head_flag_;

			//std::shared_ptr<JSL::Event>	ev_mouse;
			//std::shared_ptr<JSL::Event>	ev_keyboard;
			//std::shared_ptr<JSL::Event>	ev_gamepad;

	};
}

#endif
