#ifndef __NEB_VIEW_H__
#define __NEB_VIEW_H__

#include <memory>

#include <GUL/layout.h>

#include <glutpp/window.h>

namespace NEB
{
	class View
	{
		public:
			View();
			void				delete_scene();
			void				Display();
			
			
			std::shared_ptr<NEB::Scene>	scene_;
			std::shared_ptr<GUL::layout>	layout_;

	};
}

#endif
