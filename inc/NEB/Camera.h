#ifndef __NEB_CAMERA_H__
#define __NEB_CAMERA_H__

#include <linux/input.h>

#include <memory>
#include <map>

#include <JSL/Event.h>
#include <GRU/Window.h>



namespace NEB
{
	class Camera
	{
		public:
			enum flag: __u32
			{
				NORTH = 1 << 0,
				SOUTH = 1 << 1,
				EAST = 1 << 2,
				WEST = 1 << 3
			};

			Camera();
			void		Connect();
			void		delete_scene();
			void		SetWindow( GRU::Window* );
			void		Display();
			void		Look();
			physx::PxVec3	Move();
			void		Step(float);


			int	FirstOrderDeltaPitchRel(int);
			int	FirstOrderDeltaYawRel(int);		

			int	FirstOrderDeltaPitchAbs(float);
			int	FirstOrderDeltaYawAbs(float);		

			int	HandleAbsNorth(float);
			int	HandleAbsEast(float);

			int	HandleKeyNorth(__s32);
			int	HandleKeySouth(__s32);
			int	HandleKeyEast(__s32);
			int	HandleKeyWest(__s32);

			__s32	handle_delete_scene(__s32);

			NEB::View* view_;

			__u32	flag_;

			float pitch_;
			float yaw_;
			float v_pitch_;
			float v_yaw_;
			

			float north_;
			float east_;

			physx::PxVec3 eye_;
			
			std::map<__s32,__u32>		key_flag_;
			std::map<__s32,physx::PxVec3>	head_;
			std::map<__u32,__s32>		head_flag_;

			

			std::shared_ptr<JSL::Event>	ev_mouse;
			std::shared_ptr<JSL::Event>	ev_keyboard;
			std::shared_ptr<JSL::Event>	ev_gamepad;

	};
}

#endif
