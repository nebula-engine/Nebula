#ifndef __NEB_VIEW_H__
#define __NEB_VIEW_H__

#include <GRU/Window.h>

namespace NEB
{
	class View
	{
		public:
			void	SetWindow( GRU::Window* );
			void	Display();
			
			NEB::Scene*	scene_;
	};
}

#endif
