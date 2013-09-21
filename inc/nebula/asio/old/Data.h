#ifndef _FRAMEWORK_COMMUNICATION_MESSAGE_DATA_H
#define _FRAMEWORK_COMMUNICATION_MESSAGE_DATA_H

#include <memory>
#include <queue>

#include <Utilities/Utilities.h>

using namespace std;

namespace Framework
{
	namespace Communication
	{
		namespace Message
		{
			/// %Key %Event
			struct KeyEventData
			{
				/// %Key
				int key;
				/// %Window
				int window;
			};

			/// %Pointer %Motion
			struct MouseMove
			{
				/// x
				int x;
				/// y
				int y;
			};

			/// %Controller %State
			struct Controller_State
			{
			public:
				/// %Flag
				UINT	flag;
				/// %Pitch
				FLOAT	pitch;
				/// %Yaw
				FLOAT	yaw;
			};

			/// %Data
			struct Data
			{
				union
				{
					/// %Key %Event %Data
					KeyEventData		keyEventData;
					MouseMove			mouse_move;
					Controller_State	controller_state;
				};
			};
		}
	}
}



#endif



