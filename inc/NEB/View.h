#ifndef __NEB_VIEW_H__
#define __NEB_VIEW_H__

#include <memory>

#include <GRU/Window.h>

namespace NEB
{
	class View
	{
		public:
			View();
			void				delete_scene();
			void				Display();
			
			
			std::shared_ptr<NEB::Scene>	scene_;

	};
}

#endif
