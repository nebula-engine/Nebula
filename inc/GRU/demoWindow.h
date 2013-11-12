

#ifndef __DEMO_WINDOW_H__
#define __DEMO_WINDOW_H__

#include <GRU/Master.h>
#include <GRU/Window.h>

namespace GRU
{
	class DemoWindow : public GRU::Window
	{
		public:

			int          height, width;
			int          initPositionX, initPositionY;

			DemoWindow( GRU::Master * glutMaster,
					int setWidth, int setHeight,
					int setInitPositionX, int setInitPositionY,
					const char * title);
			~DemoWindow();

			void CallBackDisplayFunc(void);
			void CallBackReshapeFunc(int w, int h);   
			void CallBackIdleFunc(void);

			void StartSpinning( GRU::Master * glutMaster );
	};
}

#endif

