#ifndef __NEB_VIEW_H__
#define __NEB_VIEW_H__

#include <GRU/Window.h>



namespace NEB
{
	class View
	{
		public:
			View();
			void	SetWindow( GRU::Window* );
			void	Display();
			void	Look();
			
			void	FirstOrderDeltaPitch(float);
			void	FirstOrderDeltaYaw(float);		

			NEB::Scene*	scene_;

			float pitch_;
			float yaw_;
	};
}

#endif
