#ifndef __NEBULA_WINDOW_H__
#define __NEBULA_WINDOW_H__

#include <glutpp/window.h>

namespace neb
{
	class app;
	class window: public glutpp::window
	{
		public:
			window(int w, int h, int x, int y, char const * title);
			void			step(double);
			
			std::weak_ptr<neb::app>  app_;
	};
}

#endif
