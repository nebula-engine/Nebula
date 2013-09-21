#ifndef _FRAMEWORK_COMMUNICATION_MESSAGE_H
#define _FRAMEWORK_COMMUNICATION_MESSAGE_H

#include <memory>
#include <queue>

#include <utilities/Types/Utilities.h>

#include <framework/Communication/Message/FR_COM_MSG_Data.h>

using namespace std;

namespace Framework {
	namespace Communication {
		namespace Message {
			/// %Message Destination
			/** 
			Data used to route the %Message to its final destination if 
			a direct Post() is not possible (ex. message is sent over a network)
			*/
			struct Dest {
				/// %IComm pointer
				FR_COM_IComm* icomm;
		
				/// %Message Destination Type
				int type;

				union {
					struct Addr_CO_AC_AD_ActorBase {
						int universe;
						int scene;
						int actorBase;
					} acAdActorBase;
				} addr;
			};

			/// %Message Destination Type
			struct DestType {
				/// enum
				enum e {
					eCO_AC_AD_ACTORBASE
				};
			};

			/// %Message
			struct Message {
				/// %Message %Type
				int type;

				/// Destination
				Dest	dest;

				/// Data
				FR_COM_MSG_Data data;
			};

			/// %Message %Type
			struct Type {
				/// enum
				enum e {
					eINVALID,
					eKEY_UP,
					eKEY_DOWN,
					eMOUSE_MOVE
				};
			};
		}
	}
}



#endif



